/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
//Modified by Wucaihua
#include <CRCore/crCullingSet.h>

using namespace CRCore;

crCullingSet::crCullingSet()
{
    m_mask = ENABLE_ALL_CULLING;//DEFAULT_CULLING;
    m_pixelSizeVector.set(0,0,0,1);
    m_smallFeatureCullingPixelSize=1.0f;
}

crCullingSet::~crCullingSet()
{
}

//void PrintNodePath(const NodePath& nodePath)
//{
//    for(NodePath::const_iterator itr=nodePath.begin();
//        itr!=nodePath.end();
//        ++itr)
//    {
//        std::cout<<*itr<<"  ";
//    }
//}


void crCullingSet::disableAndPushOccludersCurrentMask(NodePath& nodePath)
{
    for(OccluderList::iterator itr=m_occluderList.begin();
        itr!=m_occluderList.end();
        ++itr)
    {
        //std::cout<<"    checking against ";PrintNodePath(itr->getNodePath());std::cout<<std::endl;
        if (itr->getNodePath()==nodePath)
        {
            //std::cout<<"  ++ disabling occluder "<<itr<<std::endl;
            // we have trapped for the case an occlude potentially occluding itself,
            // to prevent this we disable the results mask so that no subsequnt 
            // when the next pushCurrentMask calls happens this occluder is switched off.
            itr->disableResultMasks();
            itr->pushCurrentMask();
        }
    }
}


void crCullingSet::popOccludersCurrentMask(NodePath& nodePath)
{
    for(OccluderList::iterator itr=m_occluderList.begin();
        itr!=m_occluderList.end();
        ++itr)
    {
        //std::cout<<"    checking against ";PrintNodePath(itr->getNodePath());std::cout<<std::endl;
        if (itr->getNodePath()==nodePath)
        {
            //std::cout<<"  popping occluder "<<itr<<std::endl;
            // we have trapped for the case an occlude potentially occluding itself,
            // to prevent this we disable the results mask so that no subsequnt 
            // when the next pushCurrentMask calls happens this occluder is switched off.
            itr->popCurrentMask();
        }
    }
}

crVector4 crCullingSet::computePixelSizeVector(const crViewPort& W, const crMatrix& P, const crMatrix& M)
{
	// pre adjust P00,P20,P23,P33 by multiplying them by the viewport window matrix.
	// here we do it in short hand with the knowledge of how the window matrix is formed
	// note P23,P33 are multiplied by an implicit 1 which would come from the window matrix.
	// Robert Osfield, June 2002.

	// scaling for horizontal pixels
	float P00 = P(0,0)*W.width()*0.5f;
	float P20_00 = P(2,0)*W.width()*0.5f + P(2,3)*W.width()*0.5f;
	crVector3 scale_00(M(0,0)*P00 + M(0,2)*P20_00,
		M(1,0)*P00 + M(1,2)*P20_00,
		M(2,0)*P00 + M(2,2)*P20_00);

	// scaling for vertical pixels
	float P10 = P(1,1)*W.height()*0.5f;
	float P20_10 = P(2,1)*W.height()*0.5f + P(2,3)*W.height()*0.5f;
	crVector3 scale_10(M(0,1)*P10 + M(0,2)*P20_10,
		M(1,1)*P10 + M(1,2)*P20_10,
		M(2,1)*P10 + M(2,2)*P20_10);

	float P23 = P(2,3);
	float P33 = P(3,3);
	crVector4 pixelSizeVector(M(0,2)*P23,
		M(1,2)*P23,
		M(2,2)*P23,
		M(3,2)*P23 + M(3,3)*P33);

	float scaleRatio  = 0.7071067811f/sqrtf(scale_00.length2()+scale_10.length2());
	pixelSizeVector *= scaleRatio;

	return pixelSizeVector;
}
