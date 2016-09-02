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
#include <vector>
#include <string>
#include<conio.h>
using namespace CRCore;
using namespace CREncapsulation;
int main( int argc, char **argv )
{
	ref_ptr<crTableIO> createtab = crTableIO::openFile("JXJ/script/table/EquipRefineCreate.crb");
	ref_ptr<crTableIO> refinetab[3];
	crTableIO::StrVec title;
	title.push_back("id");
	title.push_back("����");
	title.push_back("CD����");
	title.push_back("�ƶ��ٶ�");
	title.push_back("����ֵ");
	title.push_back("ħ��");
	title.push_back("�񵲼���");
	title.push_back("������");
	title.push_back("����ֵ");
	title.push_back("������");
	title.push_back("������");
	title.push_back("���ǹ�����");
	title.push_back("��������");
	title.push_back("������");
	title.push_back("��͸");
	title.push_back("������͸");
	title.push_back("Ǳ��");
	title.push_back("��Ǳ��");
	title.push_back("��Ұ");
	title.push_back("��������");
	title.push_back("��������");
	title.push_back("��������");
	title.push_back("������Ѫ");
	title.push_back("������Ѫ");
	title.push_back("������");
	title.push_back("����");
	title.push_back("���˼���");
	title.push_back("���˼���");
	title.push_back("abstractid");
	int titlesize = title.size();
	int maxtcount = titlesize-1;
	crTableIO::StrVec record;
	crTableIO::StrVec addrecord;
	std::set<_crInt32> TVSet;
	short tid,tvalue;
	crVector2i vr;
	rangei trng(0,maxtcount);
	rangei vrange;
	int i = 0;
	crVector2i refidrange;
	int attrcountid = createtab->getTitleIndex("��������");
	int startid = createtab->getTitleIndex("����");
	int dmid0 = createtab->getTitleIndex("���˼���");
	int dmid1 = createtab->getTitleIndex("���˼���");
	int jsid = createtab->getTitleIndex("����");
	int qualitycount = createtab->getRowCount();
	int refid;
	crVector2i countvec2;
	rangei attrrange;
	int attrcount;
	for (int tableid = 0; tableid < 3; tableid++)
	{
		refinetab[tableid] = new crTableIO;
		refinetab[tableid]->setTitleVec(title);
		for( int qualityid = 0; qualityid<qualitycount; qualityid++ )
		{
			if(createtab->queryOneRecord(0,crArgumentParser::appItoa(qualityid),record)>=0)
			{
				crArgumentParser::appAtoVec(record[1],refidrange);
				crArgumentParser::appAtoVec(record[2],countvec2);
				attrrange.set(countvec2[0],countvec2[1]);
				for(refid=refidrange[0]; refid<refidrange[1]; refid++)
				{
					addrecord.clear();
					addrecord.resize(titlesize);
					addrecord[0] = crArgumentParser::appItoa(refid);
					attrcount = attrrange.get_random();
					for (i = 0; i<attrcount;i++)
					{
						do 
						{//�����Ч��tid
							tid = trng.get_random();
							//CRCore::notify(CRCore::ALWAYS)<<"maxtcount = "<<maxtcount<<"tid = "<<tid<<std::endl;
							crArgumentParser::appAtoVec(record[tid+startid],vr);
							vrange.set(vr[0],vr[1]);
							tvalue = vrange.get_random();
							if(tvalue==0)
								continue;
							if(!addrecord[tid+1].empty())
								continue;
							if(TVSet.find(MAKEINT32(tvalue,tid)) != TVSet.end())
								continue;
							TVSet.insert(MAKEINT32(tvalue,tid));
							if(tid+startid == dmid0 || tid+startid == dmid1)
								tvalue = -tvalue;
							if(tid+startid == jsid)
								addrecord[tid+1] = "400|"+crArgumentParser::appItoa(tvalue);
							else
								addrecord[tid+1] = crArgumentParser::appItoa(tvalue);
							break;
						} while (1);
					}
					refinetab[tableid]->addData(addrecord);
				}
			}
		}
		refinetab[tableid]->saveToFileNoCook("JXJ/script/table/EquipRefine"+crArgumentParser::appItoa(tableid)+".tab");
	}
	system("pause");
	return 0;
}

