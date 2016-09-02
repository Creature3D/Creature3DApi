/* Creature3D - Online Game Engine, Copyright (C) 2005 ��ƻ�(26756325@qq.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
*/
#include <creature3d.h>
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include<conio.h>
#include<commdlg.h>
using namespace CRCore;

int main( int argc, char **argv )
{
	std::string ext = ".flt";
	if(argc>1 && argv[1])
	{
		ext = ".";
		ext += argv[1];
	}
	_putenv( "CRE_WRITEIMAGE_PATH=./textures/" );

	CRIOManager::FilePathList& filePathList = CRIOManager::crRegistry::instance()->getDataFilePathList();
	filePathList.push_back("media/textures");
	filePathList.push_back("media/icon");
	filePathList.push_back("media/fonts");
	filePathList.push_back("scene");
	filePathList.push_back("data");
	filePathList.push_back("media/textures/engine");
	filePathList.push_back("media/textures/develop");
	filePathList.push_back("media/heightmap");
	filePathList.push_back("uiscene");
	CRCore::crTexture::setImageDataRequestHandler(new CREncapsulation::crImageDataRequestClass);
	CRParticle::crParticleEffect::setLoadNodeCfgHandler(new CREncapsulation::crLoadNodeCfgClass);
	CalLoader::setLoadingMode(LOADER_INVERT_V_COORD);

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[102400];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ZeroMemory(szFile, sizeof(szFile));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Cre(.cre)\0*.cre\0All(*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		std::string filePath;
		std::string fileName;
		std::vector<std::string> fileNameVec;

		filePath = ofn.lpstrFile;

		int offset = ofn.nFileOffset;
		while(strlen(ofn.lpstrFile + offset) > 1)
		{
			fileName = ofn.lpstrFile + offset;
			fileNameVec.push_back(fileName);
			offset += fileName.length() + 1;
		}

		if(fileNameVec.size()>1)
		{
			std::string pushAndPopPath;
			CRIOManager::FilePathList fpl = CRIOManager::getDataFilePathList();
			//If absolute path
			if( (filePath.length()>0 && filePath.find_first_of("/\\")==0) ||
				(filePath.length()>2 && filePath.substr(1,1)==":" && filePath.find_first_of("/\\")==2) )
			{
				pushAndPopPath = filePath;
			}
			else
			{
				pushAndPopPath = fpl.empty() ? "." : fpl.front();
				if(pushAndPopPath.empty()) pushAndPopPath = ".";
				pushAndPopPath += "/" + filePath;
			}

			fpl.push_back(pushAndPopPath);

			for( std::vector<std::string>::iterator itr = fileNameVec.begin();
				itr != fileNameVec.end();
				++itr )
			{
				fileName = filePath + "/" + *itr;
				CRCore::Timer_t start_tick = CRCore::Timer::instance()->tick();
				CRCore::notify(CRCore::ALWAYS)<<"Loading "<<fileName.c_str()<<"..."<< std::endl;

				CRCore::ref_ptr<CRCore::crNode> node = CRIOManager::readNodeFile(fileName);

				if (!node.valid()) 
				{
					//std::cout << arguments.getApplicationName() <<": No data loaded" << std::endl;
					return 1;
				}

				CRCore::Timer_t end_tick = CRCore::Timer::instance()->tick();
				//std::cout << "Time to load = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;
				CRCore::notify(CRCore::ALWAYS)<<"Time to load = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;

				//CRCore::notify(CRCore::ALWAYS)<<"Now Optimizing... "<< std::endl;
				//start_tick = CRCore::Timer::instance()->tick();

				////CRUtil::crSimplifier simplifier;
				////node->accept(simplifier);

				//CRUtil::crOptimizer optimizer;
				//optimizer.optimize(node.get(),CRUtil::crOptimizer::DEFAULT_OPTIMIZATIONS);
				////CRUtil::crSmoothingVisitor smoother;
				////node->accept(smoother);

				////�ڴ˼����BumpMap��֧�ּ���Ч��Ⱦ���ݵ�׼��
				//CRUtil::crPrepareVisitor prepareVisitor;
				//node->accept(prepareVisitor);

				//end_tick = CRCore::Timer::instance()->tick();
				//CRCore::notify(CRCore::ALWAYS)<<"Time to Optimize = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;

				fileName = CRCore::crArgumentParser::getFileNameEliminateExt(fileName) + ext;

				start_tick = CRCore::Timer::instance()->tick();
				CRCore::notify(CRCore::ALWAYS)<<"Write file "<<fileName<<"..."<< std::endl;
				if(fileName.compare(" ") == 0)
					return 1;
				CRIOManager::writeNodeFile(*node,fileName);
				end_tick = CRCore::Timer::instance()->tick();
				CRCore::notify(CRCore::ALWAYS)<<"Time to Write = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;
			}
		}
		else
		{//fileName==filePath
			fileName = filePath;
			filePath = CRIOManager::getFilePath(fileName);

			std::string pushAndPopPath;
			CRIOManager::FilePathList fpl = CRIOManager::getDataFilePathList();
			//If absolute path
			if( (filePath.length()>0 && filePath.find_first_of("/\\")==0) ||
				(filePath.length()>2 && filePath.substr(1,1)==":" && filePath.find_first_of("/\\")==2) )
			{
				pushAndPopPath = filePath;
			}
			else
			{
				pushAndPopPath = fpl.empty() ? "." : fpl.front();
				if(pushAndPopPath.empty()) pushAndPopPath = ".";
				pushAndPopPath += "/" + filePath;
			}

			fpl.push_back(pushAndPopPath);

			CRCore::Timer_t start_tick = CRCore::Timer::instance()->tick();
			CRCore::notify(CRCore::ALWAYS)<<"Loading "<<fileName.c_str()<<"..."<< std::endl;

			CRCore::ref_ptr<CRCore::crNode> node = CRIOManager::readNodeFile(fileName);

			if (!node.valid()) 
			{
				//std::cout << arguments.getApplicationName() <<": No data loaded" << std::endl;
				return 1;
			}

			CRCore::Timer_t end_tick = CRCore::Timer::instance()->tick();
			//std::cout << "Time to load = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;
			CRCore::notify(CRCore::ALWAYS)<<"Time to load = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;

			//CRCore::notify(CRCore::ALWAYS)<<"Now Optimizing... "<< std::endl;
			//start_tick = CRCore::Timer::instance()->tick();

			////CRUtil::crSimplifier simplifier;
			////node->accept(simplifier);

			//CRUtil::crOptimizer optimizer;
			//optimizer.optimize(node.get(),CRUtil::crOptimizer::DEFAULT_OPTIMIZATIONS);
			////CRUtil::crSmoothingVisitor smoother;
			////node->accept(smoother);

			////�ڴ˼����BumpMap��֧�ּ���Ч��Ⱦ���ݵ�׼��
			//CRUtil::crPrepareVisitor prepareVisitor;
			//node->accept(prepareVisitor);

			//end_tick = CRCore::Timer::instance()->tick();
			//CRCore::notify(CRCore::ALWAYS)<<"Time to Optimize = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;

			fileName = CRCore::crArgumentParser::getFileNameEliminateExt(fileName) + ext;

			start_tick = CRCore::Timer::instance()->tick();
			CRCore::notify(CRCore::ALWAYS)<<"Write file "<<fileName<<"..."<< std::endl;
			if(fileName.compare(" ") == 0)
				return 1;
			CRIOManager::writeNodeFile(*node,fileName);
			end_tick = CRCore::Timer::instance()->tick();
			CRCore::notify(CRCore::ALWAYS)<<"Time to Write = "<<CRCore::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;
		}
	}
	system("pause");
	return 0;
}