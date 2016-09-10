/* Creature3D - Online Game Engine, Copyright (C) 2005 Wucaihua(26756325@qq.com)
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
#include <CRNetApp/appPathFinding.h>
#include <CRNetApp/appNetGameData.h>
#include <CRNetApp/appClientPlayerData.h>
#include <CRNetApp/appNetPackets2.h>
#include <CRNetApp/appMsg.h>
#include <CRNet/crNetContainer.h>
#include <CRCore/crMatrixTransform.h>

using namespace CRNetApp;
using namespace CRCore;
using namespace CRNet;

///////////////////////////////////////////////////////////
//// ƽ��·��
///////////////////////////////////////////////////////////
////#undef SMOOTH_PATH
//#define SMOOTH_PATH
//// ���node�Ƿ�����
//// ���� true, node��������
////		false, node��������
//// ƽ��·������
//// ����:
//// 1 -- û�д���
//int CRNetApp::SmoothPath(const crSceneLayer *sceneLayer, const CoordDeque& path, CoordDeque& smoothPath)
//{
//	smoothPath.clear();
//	if (path.size() <= 2)
//	{
//		for (int i = 0; i < path.size(); ++i)
//			smoothPath.push_back(path.at(i));
//		return true;
//	}
//
//	CoordDeque smoothPath1;
//	smoothPath1.push_back(path.at(0));
//
//	for (int i = 0; i+2 < path.size(); )
//	{
//		int j;
//		for (j = i; j+2 < path.size(); ++j)
//		{
//			if (!(((path.at(j).x() - path.at(j+1).x()) == (path.at(j+1).x() - path.at(j+2).x())) && ((path.at(j).y() - path.at(j+1).y()) == (path.at(j+1).y() - path.at(j+2).y()))))
//			{
//				smoothPath1.push_back(path.at(j + 1));
//				break;
//			}
//		}
//		i = j + 1;
//	}
//	
//
//	smoothPath1.push_back(path.at(path.size() - 1));
//
//	smoothPath.push_back(smoothPath1.at(0));
//	for (int i = 0; i < smoothPath1.size();)
//	{
//		int j = i + 1;
//		for(; j < smoothPath1.size(); ++j)
//		{
//			if (LineHasBarrier(sceneLayer, smoothPath1.at(i), smoothPath1.at(j)))
//				break;
//		}
//		if (j >= smoothPath1.size())
//		{
//			smoothPath.push_back(smoothPath1.back());
//			return true;
//		}
//		if (j - 1 > i)
//		{
//			smoothPath.push_back(smoothPath1.at(j - 1));
//			i = j - 1;
//		}
//		else
//		{
//			//smoothPath.push_back(smoothPath1.at(j));
//			//i = j;
//			return false;
//		}
//	}
//	return false; 
//}

///////////////////////////////////
//
//crPathFinding
//
/////////////////////////////////////
int crPathFinding::s_maxSearchCount = 3000;
crPathFinding::crPathFinding():
m_startNode(new PathNode),
m_endNode(new PathNode),
//m_step(1),
m_scene(NULL),
m_sceneLayer(NULL),
m_item(NULL)
{
}
crPathFinding::~crPathFinding()
{
}

unsigned char crPathFinding::findBestPath(crInstanceItem *item, const CRCore::crVector2s &start,const CRCore::crVector2s &target, crSceneLayer *sceneLayer)
{
	reset();
	m_item = item;
	m_sceneLayer = sceneLayer;
	m_scene = m_sceneLayer->getParentScene();
	//if(item->getOrCreatePathFinder()->findTargetInPath(target))//�п��ܻ���ִ���·��
	//	return true;
	//m_openPath.clear();
	////m_closePath.resize(0);
	//m_closePath.clear();
	//m_bestPath.clear();
	m_startNode->m_coord = start;
	m_endNode->m_coord = target;
	m_currentNode = m_startNode.get();//��ʼ�ڵ�����ΪĬ�ϵ�ǰ�ڵ�
	m_currentNode->G = 0;
	m_openPath.insert(std::make_pair(0,m_startNode.get()));//��ӵ������б�
	m_findSuccess = false;
	//m_nearestNode = NULL;
	TryToFindPath(m_startNode.get());
	//CRCore::notify(CRCore::ALWAYS)<<"findBestPath(): start="<<start<<" target="<<target<<" success="<<(int)m_findSuccess<<std::endl;
	if (m_findSuccess)
	{//��ʼѰ��·��
		InsertPathNode(m_endNode.get());//���Ѱ�ҳɹ�������յ㿪ʼ�ӹر��б��а����·����ӵ����·���б�
		//CRCore::notify(CRCore::ALWAYS)<<"normal findBestPath(): start="<<start<<" target="<<target<<" success="<<(int)m_findSuccess<<std::endl;

		// ֱ��ƽ��
//#ifdef SMOOTH_PATH
		//if (smooth && crGlobalHandle::isClient() && m_bestPath.size() > 2)
		//{
		//	CoordDeque smooth;
		//	if (SmoothPath(sceneLayer, m_bestPath, smooth))
		//	{
		//		if (smooth.size() >= 2)
		//			m_bestPath.swap(smooth);
		//	}
		//}
//#endif
		return crInstanceItem::crPathFinder::Found;
	}
	return crInstanceItem::crPathFinder::NonExistent;
}
void crPathFinding::TryToFindPath(PathNode* node)
{
	//static int s_maxcount = crGlobalHandle::isClient()?5000:2000;
	if (m_openPath.size() > 0)
	{
		PathNodeMap::iterator itr = m_openPath.begin();
		//m_closePath.push_back(itr->second.get());//ÿ�δӿ����б���ȡ��һ����ӵ��ر��б�ע������б��Ѿ��������ģ���һ������Fֵ��С��
		m_closePath[itr->second->m_coord] = itr->second;//ÿ�δӿ����б���ȡ��һ����ӵ��ر��б�ע������б��Ѿ��������ģ���һ������Fֵ��С��
		//if(!m_nearestNode.valid())
		//	m_nearestNode = itr->second;
		//else if(m_nearestNode->H==0 || itr->second->H<m_nearestNode->H)
		//{
		//	m_nearestNode = itr->second;
		//}
		m_openPath.erase(itr);//�Ѹýڵ�ӿ����б����Ƴ�
	}
	/*if(node->H>200)
	{
	m_step = 4;
	}
	else if(node->H>100)
	{
	m_step = 3;
	}
	else *//*if(node->H>50)
	{
		m_step = 2;
	}
	else
	{
		m_step = 1;
	}*/

	AddOpenNode(node);//������ڵ�Ϊ��׼���������ܵĽڵ���ӵ������б��У��ų��ϰ���Ѿ��ڿ����б��ر��б��е�
	//��Ŀ��ڵ��Ѿ��ڿ����б���ʱ��ʾѰ·�ɹ�
	//PathNode *endNode = IsInOpenPath(m_endNode.get());
	if (m_findSuccess)
	{
		//m_endNode = endNode;
		//m_closePath.push_back(m_endNode.get());//��Ŀ��ڵ����ر��б���
		m_closePath[m_endNode->m_coord] = m_endNode.get();
		//m_endNode->m_parentCoord = m_currentNode->m_coord;//Ŀ��ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
		//m_findSuccess = true;
		return;
	}
	if(m_closePath.size()>s_maxSearchCount)
	{
		return;
	}
	//sortPathByF();//��Fֵ��С��������
	if (m_openPath.size() > 0)
	{
		PathNodeMap::iterator itr = m_openPath.begin();
		m_currentNode = itr->second.get();//�ӿ����б���ȡFֵ��С����Ϊ��ǰ�ڵ�
		TryToFindPath(m_currentNode.get());//�ݹ���ã��ٴ�Ѱ·
	}
}
/// �ѵ�ǰ�ڵ����ܵİ˸��ڵ㳢��ȫ����ӵ������б���
bool crPathFinding::canpass(short x, short y)
{
	return (!m_findSuccess && m_sceneLayer->walkability(x,y));
}
void crPathFinding::AddOpenNode(PathNode* node)
{
	//if(node->H<70)
	//{
		bool up = AddOneOpenNode(node->m_coord[0], node->m_coord[1] + 1, node,10);
		bool down = AddOneOpenNode(node->m_coord[0], node->m_coord[1] - 1, node,10);
		bool right = AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1], node,10);
		bool left = AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1], node,10);
		if(left && down) AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1] - 1, node,14);
		if(left && up) AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1] + 1, node,14);
		if(right && up) AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1] + 1, node,14);
		if(right && down) AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1] - 1, node,14);
	//}
	//else
	//{
	//	bool up = canpass(node->m_coord[0], node->m_coord[1] + 1);
	//	if(up) up = canpass(node->m_coord[0], node->m_coord[1] + 2);
	//	if(up) AddOneOpenNode(node->m_coord[0], node->m_coord[1] + 3, node,10);

	//	bool down = canpass(node->m_coord[0], node->m_coord[1] - 1);
	//	if(down) down = canpass(node->m_coord[0], node->m_coord[1] - 2);
	//	if(down) AddOneOpenNode(node->m_coord[0], node->m_coord[1] - 3, node,10);
	//	
	//	bool right = canpass(node->m_coord[0] + 1, node->m_coord[1]);
	//	if(right) right = canpass(node->m_coord[0] + 2, node->m_coord[1]);
	//	if(right) AddOneOpenNode(node->m_coord[0] + 3, node->m_coord[1], node,10);
	//	
	//	bool left = canpass(node->m_coord[0] - 1, node->m_coord[1]);
	//	if(left) left = canpass(node->m_coord[0] - 2, node->m_coord[1]);
	//	if(left) AddOneOpenNode(node->m_coord[0] - 3, node->m_coord[1], node,10);

	//	if(left && down)
	//	{
	//		bool leftdown = canpass(node->m_coord[0] - 1, node->m_coord[1] - 1);
	//		if(leftdown) leftdown = canpass(node->m_coord[0] - 1, node->m_coord[1] - 2);
	//		if(leftdown) leftdown = canpass(node->m_coord[0] - 2, node->m_coord[1] - 1);
	//		if(leftdown) leftdown = canpass(node->m_coord[0] - 2, node->m_coord[1] - 2);
	//		if(leftdown)
	//		{
	//			AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1] - 3, node,11);
	//			AddOneOpenNode(node->m_coord[0] - 2, node->m_coord[1] - 3, node,12);
	//			AddOneOpenNode(node->m_coord[0] - 3, node->m_coord[1] - 3, node,14);
	//			AddOneOpenNode(node->m_coord[0] - 3, node->m_coord[1] - 2, node,12);
	//			AddOneOpenNode(node->m_coord[0] - 3, node->m_coord[1] - 1, node,11);
	//		}
	//	}
	//	if(left && up)
	//	{
	//		bool leftup = canpass(node->m_coord[0] - 1, node->m_coord[1] + 1);
	//		if(leftup) leftup = canpass(node->m_coord[0] - 1, node->m_coord[1] + 2);
	//		if(leftup) leftup = canpass(node->m_coord[0] - 2, node->m_coord[1] + 1);
	//		if(leftup) leftup = canpass(node->m_coord[0] - 2, node->m_coord[1] + 2);
	//		if(leftup)
	//		{
	//			AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1] + 3, node,11);
	//			AddOneOpenNode(node->m_coord[0] - 2, node->m_coord[1] + 3, node,12);
	//			AddOneOpenNode(node->m_coord[0] - 3, node->m_coord[1] + 3, node,14);
	//			AddOneOpenNode(node->m_coord[0] - 3, node->m_coord[1] + 2, node,12);
	//			AddOneOpenNode(node->m_coord[0] - 3, node->m_coord[1] + 1, node,11);
	//		}
	//	}
	//	if(right && up)
	//	{
	//		bool rightup = canpass(node->m_coord[0] + 1, node->m_coord[1] + 1);
	//		if(rightup) rightup = canpass(node->m_coord[0] + 1, node->m_coord[1] + 2);
	//		if(rightup) rightup = canpass(node->m_coord[0] + 2, node->m_coord[1] + 1);
	//		if(rightup) rightup = canpass(node->m_coord[0] + 2, node->m_coord[1] + 2);
	//		if(rightup)
	//		{
	//			AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1] + 3, node,11);
	//			AddOneOpenNode(node->m_coord[0] + 2, node->m_coord[1] + 3, node,12);
	//			AddOneOpenNode(node->m_coord[0] + 3, node->m_coord[1] + 3, node,14);
	//			AddOneOpenNode(node->m_coord[0] + 3, node->m_coord[1] + 2, node,12);
	//			AddOneOpenNode(node->m_coord[0] + 3, node->m_coord[1] + 1, node,11);
	//		}
	//	}
	//	if(right && down)
	//	{
	//		bool rightdown = canpass(node->m_coord[0] + 1, node->m_coord[1] - 1);
	//		if(rightdown) rightdown = canpass(node->m_coord[0] + 1, node->m_coord[1] - 2);
	//		if(rightdown) rightdown = canpass(node->m_coord[0] + 2, node->m_coord[1] - 1);
	//		if(rightdown) rightdown = canpass(node->m_coord[0] + 2, node->m_coord[1] - 2);
	//		if(rightdown)
	//		{
	//			AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1] - 3, node,11);
	//			AddOneOpenNode(node->m_coord[0] + 2, node->m_coord[1] - 3, node,12);
	//			AddOneOpenNode(node->m_coord[0] + 3, node->m_coord[1] - 3, node,14);
	//			AddOneOpenNode(node->m_coord[0] + 3, node->m_coord[1] - 2, node,12);
	//			AddOneOpenNode(node->m_coord[0] + 3, node->m_coord[1] - 1, node,11);
	//		}
	//	}
	//}
}
/// ���һ���½ڵ㵽�����б���
bool crPathFinding::AddOneOpenNode(short x, short y, PathNode* parent,int g)
{
	//���ǰ����:x��y�ڵ�ǰ��ͼ��ά����Χ�ڡ����ǿ���·�������ٹر��б���Ҳ���ٿ����б���
	//if(!m_findSuccess && x>=0 && x < m_sceneLayer->getNumColumns() && y>=0 && y < m_sceneLayer->getNumRows() && m_sceneLayer->walkability(x,y))
	if(canpass(x,y))
	{
		CRCore::ref_ptr<PathNode> node = new PathNode(x,y);
		if(!IsInClosePath(node.get()) && !IsInOpenPath(node.get()))
		{
			node->m_parentNode = parent;// �½ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
			node->G = /*(m_currentNode->m_coord[0] == x || m_currentNode->m_coord[1] == y ? 10 : 14)*/g + parent->G;//��ǰ�ڵ��GֵΪ���ڵ�Gֵ+10(�ǶԽ���)��14 (�Խ���)
			node->H = 10 * (abs(m_endNode->m_coord[0] - x) + abs(m_endNode->m_coord[1] - y));//����Hֵ
			if(node->H == 0)
			{
				m_endNode = node;
				m_findSuccess = true;
			}
			else
			{
				m_openPath.insert(std::make_pair(node->F(),node.get()));
			}
			//else if(parent->G == 0)
			//{
			//	m_openPath.insert(std::make_pair(node->F(),node.get()));
			//}
			//else
			//{
			//	crVector2f coordPos = m_sceneLayer->getPosXY(crVector2s(x,y));
			//	crInstanceItem *item = m_scene->dynamicCollideTest(coordPos,m_item.get(),m_sceneLayer.get());
			//	if(!item)
			//	{
			//		m_openPath.insert(std::make_pair(node->F(),node.get()));
			//	}
			//	else
			//	{
			//		return false;
			//	}
			//}
		}
		return true;
	}
	return false;
}
/// �ӹر��б��У���Ŀ��㿪ʼ���Ų������и��ڵ㲢������ӵ����·����
void crPathFinding::InsertPathNode(PathNode* node)
{
	m_bestPath.push_front(node->m_coord);
	while(node->m_parentNode.valid())
	{
		node = node->m_parentNode.get();
		m_bestPath.push_front(node->m_coord);
	}
	m_bestPath.pop_front();//ȥ����ʼ��
	//for( PathNodeVec::iterator itr = m_closePath.begin();
	//	itr != m_closePath.end();
	//	++itr )
	//{
	//	if ((*itr)->m_coord == node->m_parentCoord)
	//		InsertPathNode(itr->get());
	//}
}
///// ��Fֵ��С��������
//void crPathFinding::sortPathByF()
//{
//	ref_ptr<PathNode> temp;
//	for (int i = 0; i < m_openPath.size(); i++)
//	{
//		for (int j = 0; j < m_openPath.size() - i - 1; j++)
//		{
//			if (m_openPath[j]->F() > m_openPath[j + 1]->F())
//			{
//				temp = m_openPath[j + 1];
//				m_openPath[j + 1] = m_openPath[j];
//				m_openPath[j] = temp;
//			}
//		}
//	}
//}
bool crPathFinding::IsInClosePath(PathNode* node)
{
	return m_closePath.find(node->m_coord) != m_closePath.end();
	//for(PathNodeVec::iterator itr = m_closePath.begin();
	//	itr != m_closePath.end();
	//	++itr)
	//{
	//	if ((*itr)->m_coord == node->m_coord)
	//		return true;
	//}
	//return false;
}
crPathFinding::PathNode* crPathFinding::IsInOpenPath(PathNode* node)
{
	for(PathNodeMap::iterator itr = m_openPath.begin();
		itr != m_openPath.end();
		++itr)
	{
		if (itr->second->m_coord == node->m_coord)
			return itr->second.get();
	}
	return NULL;
}
CoordDeque &crPathFinding::getBestPath() 
{
	return m_bestPath;
}
void crPathFinding::reset()
{
	m_openPath.clear();
	//m_closePath.resize(0);
	m_closePath.clear();
	m_bestPath.clear();
	m_item = NULL;
	m_sceneLayer = NULL;
	m_scene = NULL;
	//m_nearestNode = NULL;
	m_startNode->m_parentNode = NULL;
	m_endNode->m_parentNode = NULL;
	m_currentNode = NULL;
	//m_step = 1;
}
///////////////////////////////////
//
//crAreaPathFinding
//
/////////////////////////////////////
crAreaPathFinding::crAreaPathFinding():
m_startNode(new AreaPathNode),
m_endNode(new AreaPathNode)
{
}
crAreaPathFinding::~crAreaPathFinding()
{
}
unsigned char crAreaPathFinding::findBestPath(crArea *start, crArea *target, const crVector2f &from, const CRCore::crVector2f &to)
{
	reset();
	m_startNode->m_area = start;
	m_startNode->m_pos = from;
	m_endNode->m_area = target;
	m_endNode->m_pos = to;
	m_currentNode = m_startNode.get();//��ʼ�ڵ�����ΪĬ�ϵ�ǰ�ڵ�
	m_currentNode->G = 0;
	m_openPath.insert(std::make_pair(0,m_startNode.get()));//��ӵ������б�
	m_findSuccess = false;
	TryToFindPath(m_startNode.get());
	//CRCore::notify(CRCore::ALWAYS)<<"findBestPath(): start="<<start<<" target="<<target<<" success="<<(int)m_findSuccess<<std::endl;
	if (m_findSuccess)
	{//��ʼѰ��·��
		InsertPathNode(m_endNode.get());//���Ѱ�ҳɹ�������յ㿪ʼ�ӹر��б��а����·����ӵ����·���б�
		return crInstanceItem::crPathFinder::Found;
	}
	return crInstanceItem::crPathFinder::NonExistent;
}
void crAreaPathFinding::TryToFindPath(AreaPathNode* node)
{
	if (m_openPath.size() > 0)
	{
		AreaPathNodeMap::iterator itr = m_openPath.begin();
		m_closePath[itr->second->m_area->m_areaValue] = itr->second.get();//ÿ�δӿ����б���ȡ��һ����ӵ��ر��б�ע������б��Ѿ��������ģ���һ������Fֵ��С��
		m_openPath.erase(itr);//�Ѹýڵ�ӿ����б����Ƴ�
	}
	AddOpenNode(node);//������ڵ�Ϊ��׼���������ܵĽڵ���ӵ������б��У��ų��ϰ���Ѿ��ڿ����б��ر��б��е�
	//��Ŀ��ڵ��Ѿ��ڿ����б���ʱ��ʾѰ·�ɹ�
	//PathNode *endNode = IsInOpenPath(m_endNode.get());
	if (m_findSuccess)
	{
		//m_endNode = endNode;
		m_closePath[m_endNode->m_area->m_areaValue] = m_endNode.get();//��Ŀ��ڵ����ر��б���
		//m_endNode->m_parentCoord = m_currentNode->m_coord;//Ŀ��ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
		//m_findSuccess = true;
		return;
	}
	if(m_closePath.size()>2000)
		return;
	//sortPathByF();//��Fֵ��С��������
	if (m_openPath.size() > 0)
	{
		AreaPathNodeMap::iterator itr = m_openPath.begin();
		m_currentNode = itr->second.get();//�ӿ����б���ȡFֵ��С����Ϊ��ǰ�ڵ�
		TryToFindPath(m_currentNode.get());//�ݹ���ã��ٴ�Ѱ·
	}
}
/// �ѵ�ǰ�ڵ����ܵİ˸��ڵ㳢��ȫ����ӵ������б���
void crAreaPathFinding::AddOpenNode(AreaPathNode* node)
{
	crArea::AreaPortMap &portMap = node->m_area->m_areaPortMap;
	crArea *area;
	for( crArea::AreaPortMap::iterator itr = portMap.begin();
		itr != portMap.end();
		++itr )
	{
		area = itr->second.get();
		AddOneOpenNode(area,node);
	}
}
/// ���һ���½ڵ㵽�����б���
bool crAreaPathFinding::AddOneOpenNode(crArea *area, AreaPathNode* parent)
{
	//���ǰ����:x��y�ڵ�ǰ��ͼ��ά����Χ�ڡ����ǿ���·�������ٹر��б���Ҳ���ٿ����б���
	if(!m_findSuccess)
	{
		CRCore::ref_ptr<AreaPathNode> node = new AreaPathNode(area);
		if(!IsInClosePath(node.get()) && !IsInOpenPath(node.get()))
		{
			//node->m_parentNode = parent;// �½ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
			//node->G = 1 + parent->G;
			crVector2f port;
			float dist;
			if(area->getBestPort(parent->m_area,parent->m_pos,port,dist))
			{
				node->m_parentNode = parent;// �½ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
				node->G = parent->G + dist;
				node->m_pos = port;
				if(area->m_areaValue == m_endNode->m_area->m_areaValue)
				{
					//m_endNode = node;
					m_endNode->m_parentNode = node;
					m_findSuccess = true;
				}
				m_openPath.insert(std::make_pair(node->F(),node.get()));
				return true;
			}
		}
	}
	return false;
}
/// �ӹر��б��У���Ŀ��㿪ʼ���Ų������и��ڵ㲢������ӵ����·����
void crAreaPathFinding::InsertPathNode(AreaPathNode* node)
{
	m_bestPath.push_front(node->m_pos);
	while(node->m_parentNode.valid())
	{
		node = node->m_parentNode.get();
		m_bestPath.push_front(node->m_pos);
	}
	m_bestPath.pop_front();//ȥ����ʼ��
}
bool crAreaPathFinding::IsInClosePath(AreaPathNode* node)
{
	return m_closePath.find(node->m_area->m_areaValue)!=m_closePath.end();
	//for(AreaPathNodeVec::iterator itr = m_closePath.begin();
	//	itr != m_closePath.end();
	//	++itr)
	//{
	//	if ((*itr)->m_area->m_areaValue==node->m_area->m_areaValue)
	//		return true;
	//}
	//return false;
}
crAreaPathFinding::AreaPathNode* crAreaPathFinding::IsInOpenPath(AreaPathNode* node)
{
	for(AreaPathNodeMap::iterator itr = m_openPath.begin();
		itr != m_openPath.end();
		++itr)
	{
		if (itr->second->m_area->m_areaValue==node->m_area->m_areaValue)
			return itr->second.get();
	}
	return NULL;
}
PortDeque &crAreaPathFinding::getBestPath() 
{
	return m_bestPath;
}
void crAreaPathFinding::reset()
{
	m_openPath.clear();
	m_closePath.clear();
	m_bestPath.clear();
	m_startNode->m_parentNode = NULL;
	m_endNode->m_parentNode = NULL;
	m_currentNode = NULL;
}
///////////////////////////////////
//
//crWaypointPathFinding
//
/////////////////////////////////////
crWaypointPathFinding::crWaypointPathFinding():
	m_startNode(new WaypointPathNode),
	m_endNode(new WaypointPathNode)
{
}
crWaypointPathFinding::~crWaypointPathFinding()
{
}
unsigned char crWaypointPathFinding::findBestPath(crWaypoint *start, crWaypoint *target)
{
	reset();
	m_startNode->m_waypoint = start;
	m_endNode->m_waypoint = target;
	m_currentNode = m_startNode.get();//��ʼ�ڵ�����ΪĬ�ϵ�ǰ�ڵ�
	m_currentNode->G = 0;
	m_openPath.insert(std::make_pair(0,m_startNode.get()));//��ӵ������б�
	m_findSuccess = false;
	TryToFindPath(m_startNode.get());
	//CRCore::notify(CRCore::ALWAYS)<<"findBestPath(): start="<<start<<" target="<<target<<" success="<<(int)m_findSuccess<<std::endl;
	if (m_findSuccess)
	{//��ʼѰ��·��
		InsertPathNode(m_endNode.get());//���Ѱ�ҳɹ�������յ㿪ʼ�ӹر��б��а����·����ӵ����·���б�
		return crInstanceItem::crPathFinder::Found;
	}
	return crInstanceItem::crPathFinder::NonExistent;
}
void crWaypointPathFinding::TryToFindPath(WaypointPathNode* node)
{
	if (m_openPath.size() > 0)
	{
		WaypointPathNodeMap::iterator itr = m_openPath.begin();
		m_closePath[itr->second->m_waypoint->m_point] = itr->second.get();//ÿ�δӿ����б���ȡ��һ����ӵ��ر��б�ע������б��Ѿ��������ģ���һ������Fֵ��С��
		m_openPath.erase(itr);//�Ѹýڵ�ӿ����б����Ƴ�
	}
	AddOpenNode(node);//������ڵ�Ϊ��׼���������ܵĽڵ���ӵ������б��У��ų��ϰ���Ѿ��ڿ����б��ر��б��е�
	//��Ŀ��ڵ��Ѿ��ڿ����б���ʱ��ʾѰ·�ɹ�
	//PathNode *endNode = IsInOpenPath(m_endNode.get());
	if (m_findSuccess)
	{
		//m_endNode = endNode;
		m_closePath[m_endNode->m_waypoint->m_point] = m_endNode.get();//��Ŀ��ڵ����ر��б���
		//m_endNode->m_parentCoord = m_currentNode->m_coord;//Ŀ��ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
		//m_findSuccess = true;
		return;
	}
	if(m_closePath.size()>2000)
		return;
	//sortPathByF();//��Fֵ��С��������
	if (m_openPath.size() > 0)
	{
		WaypointPathNodeMap::iterator itr = m_openPath.begin();
		m_currentNode = itr->second.get();//�ӿ����б���ȡFֵ��С����Ϊ��ǰ�ڵ�
		TryToFindPath(m_currentNode.get());//�ݹ���ã��ٴ�Ѱ·
	}
}
/// �ѵ�ǰ�ڵ����ܵİ˸��ڵ㳢��ȫ����ӵ������б���
void crWaypointPathFinding::AddOpenNode(WaypointPathNode* node)
{
	crWaypoint::LinkMap &linkMap = node->m_waypoint->m_linkmap;
	ref_ptr<crWaypoint> wp;
	for( crWaypoint::LinkMap::iterator itr = linkMap.begin();
		itr != linkMap.end();
		++itr )
	{
		wp = itr->first;
		AddOneOpenNode(wp.get(),node);
	}
}
/// ���һ���½ڵ㵽�����б���
bool crWaypointPathFinding::AddOneOpenNode(crWaypoint *wp, WaypointPathNode* parent)
{
	//���ǰ����:x��y�ڵ�ǰ��ͼ��ά����Χ�ڡ����ǿ���·�������ٹر��б���Ҳ���ٿ����б���
	if(!m_findSuccess)
	{
		CRCore::ref_ptr<WaypointPathNode> node = new WaypointPathNode(wp);
		if(!IsInClosePath(node.get()) && !IsInOpenPath(node.get()))
		{
			node->m_parentNode = parent;// �½ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
			node->G = parent->m_waypoint->getLinkDist(wp) + parent->G;//��ǰ�ڵ��GֵΪ���ڵ�Gֵ+10(�ǶԽ���)��14 (�Խ���)
			node->H = 10 * (abs(m_endNode->m_waypoint->m_point[0] - wp->m_point[0]) + abs(m_endNode->m_waypoint->m_point[1] - wp->m_point[1]));//����Hֵ
			if(node->H == 0)
			{
				m_endNode = node;
				m_findSuccess = true;
			}
			else
			{
				m_openPath.insert(std::make_pair(node->F(),node.get()));
			}
		}
		return true;
	}
	return false;
}
/// �ӹر��б��У���Ŀ��㿪ʼ���Ų������и��ڵ㲢������ӵ����·����
void crWaypointPathFinding::InsertPathNode(WaypointPathNode* node)
{
	m_bestPath.push_front(node->m_waypoint->m_point);
	while(node->m_parentNode.valid())
	{
		node = node->m_parentNode.get();
		m_bestPath.push_front(node->m_waypoint->m_point);
	}
	m_bestPath.pop_front();//ȥ����ʼ��
}
bool crWaypointPathFinding::IsInClosePath(WaypointPathNode* node)
{
	return m_closePath.find(node->m_waypoint->m_point)!=m_closePath.end();
	//for(AreaPathNodeVec::iterator itr = m_closePath.begin();
	//	itr != m_closePath.end();
	//	++itr)
	//{
	//	if ((*itr)->m_area->m_areaValue==node->m_area->m_areaValue)
	//		return true;
	//}
	//return false;
}
crWaypointPathFinding::WaypointPathNode* crWaypointPathFinding::IsInOpenPath(WaypointPathNode* node)
{
	for(WaypointPathNodeMap::iterator itr = m_openPath.begin();
		itr != m_openPath.end();
		++itr)
	{
		if (itr->second->m_waypoint==node->m_waypoint)
			return itr->second.get();
	}
	return NULL;
}
CoordDeque &crWaypointPathFinding::getBestPath() 
{
	return m_bestPath;
}
void crWaypointPathFinding::reset()
{
	m_openPath.clear();
	m_closePath.clear();
	m_bestPath.clear();
	m_startNode->m_parentNode = NULL;
	m_endNode->m_parentNode = NULL;
	m_currentNode = NULL;
}
///////////////////////////////////
//
//crDynamicPathFinding
//
/////////////////////////////////////
crDynamicPathFinding::crDynamicPathFinding():
m_startNode(new PathNode),
m_endNode(new PathNode),
m_scene(NULL),
m_sceneLayer(NULL)
{
}
crDynamicPathFinding::~crDynamicPathFinding()
{
}
unsigned char crDynamicPathFinding::findBestPath(crInstanceItem *item, CRCore::crVector2s& start, CRCore::crVector2s& target, crSceneLayer *sceneLayer)
{
	reset();
	if(start == target)
		return crInstanceItem::crPathFinder::Lapover;
	m_sceneLayer = sceneLayer;
	m_scene = m_sceneLayer->getParentScene();
	if( start[0]<0 || start[0]>=sceneLayer->getNumColumns() || 
		start[1]<0 || start[1]>=sceneLayer->getNumRows() || 
		target[0]<0 || target[0]>=sceneLayer->getNumColumns() ||
		target[1]<0 || target[1]>=sceneLayer->getNumRows() )
		return crInstanceItem::crPathFinder::OutMap;
	m_item = item;
	m_startNode->m_coord = start;
	m_endNode->m_coord = target;
	m_currentNode = m_startNode.get();//��ʼ�ڵ�����ΪĬ�ϵ�ǰ�ڵ�
	m_currentNode->G = 0;
	m_openPath.insert(std::make_pair(0,m_startNode.get()));//��ӵ������б�
	m_findSuccess = false;
	TryToFindPath(m_startNode.get());
	if (m_findSuccess)
	{//��ʼѰ��·��
		InsertPathNode(m_endNode.get());//���Ѱ�ҳɹ�������յ㿪ʼ�ӹر��б��а����·����ӵ����·���б�
		return crInstanceItem::crPathFinder::Found;
	}
	return crInstanceItem::crPathFinder::NonExistent;
}
void crDynamicPathFinding::TryToFindPath(PathNode* node)
{
	if (m_openPath.size() > 0)
	{
		PathNodeMap::iterator itr = m_openPath.begin();
		m_closePath[itr->second->m_coord] = itr->second;//ÿ�δӿ����б���ȡ��һ����ӵ��ر��б�ע������б��Ѿ��������ģ���һ������Fֵ��С��
		m_openPath.erase(itr);//�Ѹýڵ�ӿ����б����Ƴ�
	}
	AddOpenNode(node);//������ڵ�Ϊ��׼���������ܵĽڵ���ӵ������б��У��ų��ϰ���Ѿ��ڿ����б��ر��б��е�
	if (m_findSuccess)
	{
		m_closePath[m_endNode->m_coord] = m_endNode.get();
		return;
	}
	if(m_closePath.size()>1000)
	{
		return;
	}
	if (m_openPath.size() > 0)
	{
		PathNodeMap::iterator itr = m_openPath.begin();
		m_currentNode = itr->second.get();//�ӿ����б���ȡFֵ��С����Ϊ��ǰ�ڵ�
		TryToFindPath(m_currentNode.get());//�ݹ���ã��ٴ�Ѱ·
	}
}
/// �ѵ�ǰ�ڵ����ܵİ˸��ڵ㳢��ȫ����ӵ������б���
void crDynamicPathFinding::AddOpenNode(PathNode* node)
{
	bool up = AddOneOpenNode(node->m_coord[0], node->m_coord[1] + 1, node,10);
	bool down = AddOneOpenNode(node->m_coord[0], node->m_coord[1] - 1, node,10);
	bool right = AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1], node,10);
	bool left = AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1], node,10);

	if(left && down) AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1] - 1, node,14);
	if(left && up) AddOneOpenNode(node->m_coord[0] - 1, node->m_coord[1] + 1, node,14);
	if(right && up) AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1] + 1, node,14);
	if(right && down) AddOneOpenNode(node->m_coord[0] + 1, node->m_coord[1] - 1, node,14);
}
/// ���һ���½ڵ㵽�����б���
bool crDynamicPathFinding::AddOneOpenNode(short x, short y, PathNode* parent,int g)
{
	//���ǰ����:x��y�ڵ�ǰ��ͼ��ά����Χ�ڡ����ǿ���·�������ٹر��б���Ҳ���ٿ����б���
	if(!m_findSuccess && m_sceneLayer->walkability(x,y))
	{
		CRCore::ref_ptr<PathNode> node = new PathNode(x,y);
		if(!IsInClosePath(node.get()) && !IsInOpenPath(node.get()))
		{
			node->m_parentNode = parent;// �½ڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
			node->G = /*(m_currentNode->m_coord[0] == x || m_currentNode->m_coord[1] == y ? 10 : 14)*/g + parent->G;//��ǰ�ڵ��GֵΪ���ڵ�Gֵ+10(�ǶԽ���)��14 (�Խ���)
			node->H = 10 * (abs(m_endNode->m_coord[0] - x) + abs(m_endNode->m_coord[1] - y));//����Hֵ
			if(node->H == 0)
			{
				m_endNode = node;
				m_findSuccess = true;
			}
			else
			{
				crVector2f coordPos = m_sceneLayer->getPosXY(crVector2s(x,y));
				bool ignore = (abs(m_startNode->m_coord[0]-x)+abs(m_startNode->m_coord[1]-y))<8;
				if(ignore)
				{
					m_openPath.insert(std::make_pair(node->F(),node.get()));
				}
				else
				{
					crInstanceItem *item = m_scene->dynamicCollideTest(coordPos,m_item.get(),m_sceneLayer.get(),IG_Me);
					if(!item)
					{
						m_openPath.insert(std::make_pair(node->F(),node.get()));
					}
					else
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	return false;
}
/// �ӹر��б��У���Ŀ��㿪ʼ���Ų������и��ڵ㲢������ӵ����·����
void crDynamicPathFinding::InsertPathNode(PathNode* node)
{
	m_bestPath.push_front(node->m_coord);
	while(node->m_parentNode.valid())
	{
		node = node->m_parentNode.get();
		m_bestPath.push_front(node->m_coord);
	}
	m_bestPath.pop_front();//ȥ����ʼ��
}
bool crDynamicPathFinding::IsInClosePath(PathNode* node)
{
	return m_closePath.find(node->m_coord) != m_closePath.end();
}
crDynamicPathFinding::PathNode* crDynamicPathFinding::IsInOpenPath(PathNode* node)
{
	for(PathNodeMap::iterator itr = m_openPath.begin();
		itr != m_openPath.end();
		++itr)
	{
		if (itr->second->m_coord == node->m_coord)
			return itr->second.get();
	}
	return NULL;
}
CoordDeque &crDynamicPathFinding::getBestPath() 
{
	return m_bestPath;
}
void crDynamicPathFinding::reset()
{
	m_openPath.clear();
	m_closePath.clear();
	m_bestPath.clear();
	m_item = NULL;
	m_sceneLayer = NULL;
	m_scene = NULL;
	m_startNode->m_parentNode = NULL;
	m_endNode->m_parentNode = NULL;
	m_currentNode = NULL;
}
///////////////////////////////////
//
//crPathFindingManager
//
/////////////////////////////////////
//unsigned char crPathFindingManager::s_pathFindingCount = 1;
crPathFindingManager::crPathFindingManager():
m_scene(NULL)
{
	m_pathFinding = new crPathFinding;
	m_areaPathFinding = new crAreaPathFinding;
	m_waypointPathFinding = new crWaypointPathFinding;
	m_pathFinding->setMaxSearchCount(crGlobalHandle::isClient()?5000:3000);
}
crPathFindingManager::~crPathFindingManager()
{

}
//void crPathFindingManager::setPathFindingCount(unsigned char count)
//{
//	s_pathFindingCount = count;
//	crPathFindingUpdater::getInstance()->startThread();
//}
void crPathFindingManager::init(crScene *scene)
{
	m_scene = scene;
	//m_pathFindingVec.clear();
	//for(int i = 0; i<s_pathFindingCount;i++)
	//{
	//	m_pathFindingVec.push_back(new crPathFinding);
	//}
	crPathFindingUpdater::getInstance()->registerPathFindingManager(this);
}
void crPathFindingManager::addPathFindRequest(crInstanceItem *item)
{
	if(item->isMainAI() && !isInRequestDeque(item))
	{
		unsigned int guisestate = GS_Normal;
		item->doEvent(MAKEINT64(WCH_GetGuiseState,0),MAKEINT64(&guisestate,NULL));
		if(guisestate & GS_UnVisiable || guisestate & GS_Garrison || guisestate & GS_Fetter || guisestate & GS_Swoon || guisestate & GS_Stagnate || guisestate & GS_ExtraShifting || guisestate & GS_Confusion)
		{//�����ƶ�
			return;
		}
		item->getOrCreatePathFinder()->refind();
		//crData *data = item->getDataClass();
		//crVector3 from = item->getPosition();
		//void *param;
		//data->getParam(WCHDATA_TargetPos,param);
		//crVector3 targetPos = *(crVector3 *)param;
		//crVector2 dir(targetPos[0] - from[0], targetPos[1] - from[1]);
		//if(dir.length()<1.0f)
		//	return;
		addWaypointFindRequest(item);
	}
}
void crPathFindingManager::recvPathFindRequest(crInstanceItem *item)
{
	item->getOrCreatePathFinder()->refind();
	//crData *data = item->getDataClass();
	//crVector3 from = item->getPosition();
	//void *param;
	//data->getParam(WCHDATA_TargetPos,param);
	//crVector3 targetPos = *(crVector3 *)param;
	//crVector2 dir(targetPos[0] - from[0], targetPos[1] - from[1]);
	//if(dir.length()<1.0f)
	//	return;
	addWaypointFindRequest(item);
}
void crPathFindingManager::addWaypointFindRequest(crInstanceItem *item)
{
	GNE::LockMutex lock( m_requestDequeMutex );
	for( RequestDeque::iterator itr = m_requestDeque.begin();
		itr != m_requestDeque.end();
		++itr )
	{
		if(itr->get() == item)
			return;
	}
	//if(crGlobalHandle::isClient())
	//{
	//	if(crMyPlayerData::getInstance()->ifItemIsMe(item))
	//		m_requestDeque.push_front(item);
	//	else
	//		m_requestDeque.push_back(item);
	//}
	//else
	m_requestDeque.push_back(item);
}
bool crPathFindingManager::isInRequestDeque(crInstanceItem *item)
{
	GNE::LockMutex lock( m_requestDequeMutex );
	for( RequestDeque::iterator itr = m_requestDeque.begin();
		itr != m_requestDeque.end();
		++itr )
	{
		if(itr->get() == item)
			return true;
	}
	return false;
}
void crPathFindingManager::update()
{
	ref_ptr<crInstanceItem>item;
	crSceneLayer *sceneLayer;
	void *param;
	ref_ptr<crData>data;
	crInstanceItem::crPathFinder *pathFinder;
	ref_ptr<crInstanceItem> targetItem;
	crVector3 from,targetPos;
	unsigned char itemState,found;
	//float followDistance,length;
	crVector2 dir,port,portDir;
	PortDeque portPath;
	//unsigned char targettype = Target_Coord;
	ref_ptr<crStreamBuf> stream;
	crPlayerEventPacket ppacket;
	crItemEventPacket ipacket;
	//crNetConductor *netConductor = NULL;
	crWaypoint *waypointRoot;
	crWaypoint *startWP,*targetWP;
	crVector2s start,target;
	CoordDeque inpath,bestpath;
	//if(crGlobalHandle::isClient())
	//	netConductor = crNetContainer::getInstance()->getDynamicNetConductor(GameClient_Game);
	//else
	//	netConductor = crNetContainer::getInstance()->getNetConductor(SceneServer);
	{
		GNE::LockMutex lock( m_requestDequeMutex );
		m_requestDeque_buf.swap(m_requestDeque);
	}
#if 1
	CRCore::Timer_t start_tick,end_tick;
	int count = m_requestDeque_buf.size();
	if(count>1000)
	{
		start_tick = CRCore::Timer::instance()->tick();
	}
#endif
	while(!m_requestDeque_buf.empty())
	{
		//m_requestDequeMutex.acquire();
		item = m_requestDeque_buf.front().get();
		m_requestDeque_buf.pop_front();
		//m_requestDequeMutex.release();
		if(item->getSceneID() == m_scene->getSceneID() && item->isMainAI())
		{
			sceneLayer = m_scene->getSceneLayer(item->getLayerID());
			data = item->getDataClass();
			if(sceneLayer && data.valid())
			{
				data->getParam(WCHDATA_ItemState,param);
				itemState = *(unsigned char *)param;
				if(itemState>=IS_Move)
				{
					pathFinder = item->getOrCreatePathFinder();
					from = item->getPosition();
					data->getParam(WCHDATA_TargetPos,param);
					targetPos = *(crVector3 *)param;
					start = sceneLayer->getCoord(from[0],from[1]);
					target = sceneLayer->getCoord(targetPos[0],targetPos[1]);
					if(start == target)
					{
						//item->setPosxy(targetPos[0]/crGlobalHandle::gData()->gUnitScale(),targetPos[1]/crGlobalHandle::gData()->gUnitScale());
						pathFinder->setPathStatus(crInstanceItem::crPathFinder::NonExistent);
						continue;
					}
					if(!sceneLayer->walkability(target[0],target[1]))
					{//Ѱ��target�������ߵĵ�
						short search = 1;
						short x,y;
						do
						{
							x = target[0];
							y = target[1] + search;
							if(sceneLayer->walkability(x,y))
								break;
							x = target[0];
							y = target[1] - search;
							if(sceneLayer->walkability(x,y))
								break;
							x = target[0] + search;
							y = target[1];
							if(sceneLayer->walkability(x,y))
								break;
							x = target[0] - search;
							y = target[1];
							if(sceneLayer->walkability(x,y))
								break;
							x = target[0] - search;
							y = target[1] - search;
							if(sceneLayer->walkability(x,y))
								break;
							x = target[0] - search;
							y = target[1] + search;
							if(sceneLayer->walkability(x,y))
								break;
							x = target[0] + search;
							y = target[1] + search;
							if(sceneLayer->walkability(x,y))
								break;
							x = target[0] + search;
							y = target[1] - search;
							if(sceneLayer->walkability(x,y))
								break;
							search++;
						} while (1);
						target.set(x,y);
					}
					if(start == target)
					{
						//item->setPosxy(targetPos[0]/crGlobalHandle::gData()->gUnitScale(),targetPos[1]/crGlobalHandle::gData()->gUnitScale());
						pathFinder->setPathStatus(crInstanceItem::crPathFinder::NonExistent);
						continue;
					}
					waypointRoot = sceneLayer->getWaypointRoot();
					if(!waypointRoot)
					{
						CRCore::notify(CRCore::ALWAYS)<<m_scene->getSceneName()<<" �ó���û��WaypointRoot"<<std::endl;
						//if(pathFinder->isPortPathEmpty() && pathFinder->isWaypointEmpty())
						//{
						//	portPath.clear();
						//	if(sceneLayer->findAreaPorts(start,target,portPath,m_areaPathFinding.get()) && !portPath.empty())
						//	{
						//		port = portPath.front();
						//		portDir.set(port[0] - from[0], port[1] - from[1]);
						//		//portDir.normalize();
						//		//dir.normalize();
						//		if(/*portDir * dir < 0.0f || */portDir.length2()<crGlobalHandle::gData()->gPortScopeSqr())
						//		{
						//			portPath.pop_front();
						//			if(!portPath.empty())
						//				port = portPath.front();
						//		}
						//		targetPos.set(port[0],port[1],0.0f);
						//		item->getDataClass()->inputParam(WCHDATA_TargetPos,&targetPos);
						//		//item->getDataClass()->inputParam(WCHDATA_TargetType,&targettype);
						//		item->getOrCreatePathFinder()->setPortPathDeque(portPath);
						//		target = sceneLayer->getCoord(targetPos[0],targetPos[1]);
						//	}
						//	else
						//	{
						//		//crThread::sleep(5);
						//		pathFinder->setPathStatus(crInstanceItem::crPathFinder::NonExistent);
						//		continue;
						//	}
						//}
						//else
						//{
						//	pathFinder->setPathStatus(crInstanceItem::crPathFinder::NonExistent);
						//}
					}
					else
					{
						waypointRoot->resetNearest();
						startWP = waypointRoot->searchNearest(start);
						if(!startWP)
							startWP = waypointRoot->getNearest();
						waypointRoot->endtravel();
						waypointRoot->resetNearest();
						targetWP = waypointRoot->searchNearest(target);
						if(!targetWP)
							targetWP = waypointRoot->getNearest();
						waypointRoot->endtravel();
						if(startWP && targetWP && startWP != targetWP)
						{
							found = m_waypointPathFinding->findBestPath(startWP,targetWP);
							if(found == crInstanceItem::crPathFinder::Found)
							{
								CoordDeque& bestWPDeque = m_waypointPathFinding->getBestPath();
								found = crInstanceItem::crPathFinder::Found;
								if(start != startWP->getPoint())
								{
									found = m_pathFinding->findBestPath(item.get(),start,startWP->getPoint(),sceneLayer);
								}
								if(found == crInstanceItem::crPathFinder::Found)
								{
									bestpath = m_pathFinding->getBestPath();
									if(target != targetWP->getPoint())
									{
										found = m_pathFinding->findBestPath(item.get(),targetWP->getPoint(),target,sceneLayer);
									}
									if(found == crInstanceItem::crPathFinder::Found)
									{
										CoordDeque& endpath = m_pathFinding->getBestPath();
										bestpath.insert(bestpath.end(),bestWPDeque.begin(),bestWPDeque.end());
										bestpath.insert(bestpath.end(),endpath.begin(),endpath.end());
										//for( CoordDeque::iterator itr = bestWPDeque.begin();
										//	 itr != bestWPDeque.end();
										//	 ++itr )
										//{
										//	bestpath.push_back(*itr);
										//}
										//for( CoordDeque::iterator itr = endpath.begin();
										//	itr != endpath.end();
										//	++itr )
										//{
										//	bestpath.push_back(*itr);
										//}
										bestpath.push_front(start);
										if (bestpath.size() > 2)
										{// ֱ��ƽ��
											inpath = bestpath;
											bestpath.clear();
											SmoothPath(sceneLayer, inpath, bestpath);
										}
										bestpath.pop_front();
										pathFinder->setBestPath(bestpath);
									}
									else
									{
										pathFinder->setPathStatus(found);
										CRCore::notify(CRCore::ALWAYS)<<m_scene->getSceneName()<<" FindBestPath û���ҵ�·�� From:"<<sceneLayer->getPosXY(targetWP->getPoint())<<"To:"<<sceneLayer->getPosXY(target)<<" ����ֵ:"<<m_pathFinding->getClosePathCount()<<std::endl;
									}
								}
								else
								{
									pathFinder->setPathStatus(found);
									CRCore::notify(CRCore::ALWAYS)<<m_scene->getSceneName()<<" FindBestPath û���ҵ�·�� From:"<<sceneLayer->getPosXY(start)<<"To:"<<sceneLayer->getPosXY(startWP->getPoint())<<" ����ֵ:"<<m_pathFinding->getClosePathCount()<<std::endl;
								}
								m_pathFinding->reset();
								m_waypointPathFinding->reset();
								continue;
							}
							else
							{
								CRCore::notify(CRCore::ALWAYS)<<m_scene->getSceneName()<<" FindBestWaypoint û���ҵ�ͨ· From:"<<sceneLayer->getPosXY(start)<<"To:"<<sceneLayer->getPosXY(target)<<" ����ֵ:"<<m_waypointPathFinding->getClosePathCount()<<std::endl;
								m_waypointPathFinding->reset();
								pathFinder->setPathStatus(crInstanceItem::crPathFinder::NonExistent);
							}
						}
						else
						{
							//CRCore::notify(CRCore::ALWAYS)<<m_scene->getSceneName()<<" FindBestWaypoint û���ҵ�·�� From:"<<start<<"To:"<<target<<std::endl;
							pathFinder->setPathStatus(crInstanceItem::crPathFinder::NonExistent);
						}
					}
					found = m_pathFinding->findBestPath(item.get(),start,target,sceneLayer);
					if(found == crInstanceItem::crPathFinder::Found)
					{
						bestpath = m_pathFinding->getBestPath();
						bestpath.push_front(start);
						if (bestpath.size() > 2)
						{// ֱ��ƽ��
							inpath = bestpath;
							bestpath.clear();
							SmoothPath(sceneLayer, inpath, bestpath);
						}
						bestpath.pop_front();
						pathFinder->setBestPath(bestpath);
						//if(m_pathFinding->getClosePathCount()>500)
						//	CRCore::notify(CRCore::ALWAYS)<<"FindBestPath�ҵ�·�� From:"<<from<<"To:"<<targetPos<<" ����ֵ:"<<m_pathFinding->getClosePathCount()<<std::endl;
					}
					else
					{
						pathFinder->setPathStatus(found);
						CRCore::notify(CRCore::ALWAYS)<<m_scene->getSceneName()<<" FindBestPath û���ҵ�·�� From:"<<from<<"To:"<<targetPos<<" ����ֵ:"<<m_pathFinding->getClosePathCount()<<std::endl;
					}
					m_pathFinding->reset();
				}
			}
		}
		//crThread::sleep(5);
	}
#if 1
	if(count>1000)
	{
		end_tick = CRCore::Timer::instance()->tick();
		CRCore::notify(CRCore::ALWAYS)<<"Ѱ·����:"<<count<<" ��ʱ:"<<CRCore::Timer::instance()->delta_m(start_tick,end_tick)<<std::endl;
	}
#endif
}
void crPathFindingManager::SmoothPath(const crSceneLayer *sceneLayer, CoordDeque& inpath, CoordDeque& outpath)
{
	if(!inpath.empty())
	{
		if(outpath.empty())
		{
			outpath.push_front(*inpath.rbegin());
			inpath.pop_back();
		}
		crVector2s start = outpath.front();
		bool found = false;
		for( CoordDeque::iterator itr = inpath.begin();
			 itr != inpath.end();
			 ++itr )
		{
			if(!LineHasBarrier(sceneLayer,start,*itr))
			{//û���赲
				outpath.push_front(*itr);
				inpath.erase(itr,inpath.end());
				found = true;
				break;
			}
		}
		if(!found)
		{
			outpath.push_front(*inpath.rbegin());
			inpath.pop_back();
		}
		SmoothPath(sceneLayer,inpath,outpath);
	}
}
bool crPathFindingManager::NodeHasBarrier(const crSceneLayer *sceneLayer, const CRCore::crVector2s& node)
{
	if (sceneLayer->walkability(node.x(), node.y()))
		return false;
	return true;
}
bool crPathFindingManager::NodeHasBarrier(const crSceneLayer *sceneLayer, const short x, const short y)
{
	if (sceneLayer->walkability(x, y))
		return false;
	return true;
}
void crPathFindingManager::XGetNode(float x, float y, CRCore::crVector2s& outNode)
{
	outNode.x() = (int)(x);
	if (y >= 0)
		outNode.y() = (y - floor(y))>=0.5f ? (int)ceil(y) : (int)floor(y);
	else
		outNode.y() = (ceil(y) - y)>=0.5f ? (int)floor(y) : (int)ceil(y);
}
void crPathFindingManager::YGetNode(float x, float y, CRCore::crVector2s& outNode)
{
	outNode.y() = (int)(y);
	if (y >= 0)
		outNode.x() = (x - floor(x))>=0.5f ? (int)ceil(x) : (int)floor(x);
	else
		outNode.x() = (ceil(x) - x)>=0.5f ? (int)floor(x) : (int)ceil(x);
}
//�ж����ڵ�֮���Ƿ�����ϰ���
bool crPathFindingManager::LineHasBarrier(const crSceneLayer *sceneLayer, const CRCore::crVector2s& start, const CRCore::crVector2s& end)
{
	int distX = abs(end.x() - start.x());
	int distY = abs(end.y() - start.y());

	if (distX == 0)
	{
		int loopStart = MIN( start.y(), end.y() );
		int loopEnd = MAX( start.y(), end.y() );
		for(int i = loopStart; i <= loopEnd; ++i)
		{
			CRCore::crVector2s node(start.x(), i);
			if (NodeHasBarrier(sceneLayer, node))
				return true;
		}
		return false;
	}
	if (distY == 0)
	{
		int loopStart = MIN( start.x(), end.x() );
		int loopEnd = MAX( start.x(), end.x() );
		for(int i = loopStart; i <= loopEnd; ++i)
		{
			CRCore::crVector2s node(i, start.y());
			if (NodeHasBarrier(sceneLayer, node))
				return true;
		}
		return false;
	}	

	bool loopDirection = distX >= distY ? true : false;
	if (loopDirection)
	{
		float a = (float)(start.y() - end.y())/(float)(start.x() - end.x());
		float b = (float)start.y() - a*(float)start.x();

		int loopStart = MIN( start.x(), end.x() );
		int loopEnd = MAX( start.x(), end.x() );
		float x = (float)loopStart;
		float y = a * x + b;
		for (int i = loopStart; i <= loopEnd; ++i)
		{
			CRCore::crVector2s node1(0, 0);
			XGetNode(x, y, node1);

			if (NodeHasBarrier(sceneLayer, node1))
				return true;
			if (i == loopEnd)
				return false;
			if (NodeHasBarrier(sceneLayer, node1.x() + 1,			node1.y()))
				return true;
			if (NodeHasBarrier(sceneLayer, node1.x() + 1,			node1.y() + ((a>0)?1:-1)))
				return true;
			if (NodeHasBarrier(sceneLayer, node1.x(), 				node1.y() + ((a>0)?1:-1)))
				return true;
			x += 1.0f;
			y = a * x + b;
		}
	}
	else
	{
		float a = (float)(start.y() - end.y())/(float)(start.x() - end.x());
		float b = (float)start.y() - a*(float)start.x();
		float ia = 1/a;

		int loopStart = MIN( start.y(), end.y() );
		int loopEnd = MAX( start.y(), end.y() );
		float y = (float)loopStart;
		float x = (y - b) * ia;
		for (int i = loopStart; i <= loopEnd; ++i)
		{
			CRCore::crVector2s node1(0, 0);
			YGetNode(x, y, node1);

			if (NodeHasBarrier(sceneLayer, node1))
				return true;
			if (i == loopEnd)
				return false;
			if (NodeHasBarrier(sceneLayer, node1.x() + ((a>0)?1:-1), 			node1.y()))
				return true;
			if (NodeHasBarrier(sceneLayer, node1.x() + ((a>0)?1:-1), 			node1.y() + 1))
				return true;
			if (NodeHasBarrier(sceneLayer, node1.x(),							node1.y() + 1))
				return true;

			y = y + 1.0f;
			x = (y - b) * ia;
		}
	}
	return false;
}
///////////////////////////////////
//
//crPathFindingUpdater
//
/////////////////////////////////////
ref_ptr<crPathFindingUpdater> crPathFindingUpdater::m_instance = NULL;

crPathFindingUpdater* crPathFindingUpdater::getInstance()
{
	if (m_instance==NULL) 
	{
		m_instance = new crPathFindingUpdater;
		crBrain::getInstance()->pushInstance(m_instance.get());
	}
	return m_instance.get();
}
void crPathFindingUpdater::clear()
{
	m_instance = NULL;
}

crPathFindingUpdater::crPathFindingUpdater()
	:m_done(true)
{
}

crPathFindingUpdater::~crPathFindingUpdater() 
{
	m_done = true;
	while (isRunning()) 
	{
		CRCore::crThread::sleep(10);
	}
}

void crPathFindingUpdater::done()
{
	m_done = true;
}
void crPathFindingUpdater::registerPathFindingManager(crPathFindingManager *manager)
{
	GNE::LockMutex lock( m_pathFindingManagerMutex );
	m_pathFindingManagerVec.push_back(manager);
}
void crPathFindingUpdater::run()
{
#if _DEBUG
	try
	{
#endif
		float delta = crGlobalHandle::isClient()?0.02f:0.04f;
		m_done = false;
		CRCore::Timer_t t1 = 0L;
		CRCore::Timer_t time = t1;
		float dt;
		while(!m_done)
		{
			t1 = CRCore::Timer::instance()->tick();
			if(time == 0)
			{
				time = t1;
				CRCore::crThread::sleep(40);
				continue;
			}
			dt = CRCore::Timer::instance()->delta_s( time, t1 );
			if(dt<delta)
			{
				CRCore::crThread::sleep((delta-dt)*1000);
			}
			else
			{
				CRCore::crThread::sleep(10);
			}
			t1 = CRCore::Timer::instance()->tick();
			//dt = CRCore::Timer::instance()->delta_s( time, t1 );
			time = t1;
			{
				m_pathFindingManagerMutex.acquire();
				for( PathFindingManagerVec::iterator itr = m_pathFindingManagerVec.begin();
					itr != m_pathFindingManagerVec.end();
					++itr )
				{
					(*itr)->update();
				}
				m_pathFindingManagerMutex.release();
			}
			//sleep(10);
		}
#if _DEBUG
		CRCore::notify(CRCore::ALWAYS)<<"crPathFindingUpdater end"<<std::endl;
	}
	catch (...)
	{
		CRCore::notify(CRCore::ALWAYS)<<"crPathFindingUpdater::run() error "<<std::endl;
	}
#endif
}