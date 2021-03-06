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
#ifndef CRCORE_REFNODEPATH
#define CRCORE_REFNODEPATH 1

#include <CRCore/crGroup.h>

namespace CRCore {

class RefNodePath : public NodeArray
{
    public :
    
        inline RefNodePath() {}

        inline RefNodePath(const RefNodePath& refNodePath):
            NodeArray(refNodePath) {}

        inline explicit RefNodePath(const NodePath& nodePath)
        {
            for(CRCore::NodePath::const_iterator itr=nodePath.begin();
                itr != nodePath.end();
                ++itr)
            {
                push_back(*itr);
            }
        }
        
        RefNodePath& operator = (const RefNodePath& rhs)
        {
            if (&rhs == this) return *this;
            
            NodeArray::operator = (rhs);            
            
            return *this;
        }
        
        RefNodePath& operator = (const NodePath& rhs)
        {
            clear();
            for(CRCore::NodePath::const_iterator itr=rhs.begin();
                itr != rhs.end();
                ++itr)
            {
                push_back(*itr);
            }
            
            return *this;
        }

        inline operator NodePath () const
        {
            NodePath nodePath;
            for(NodeArray::const_iterator itr=begin();
                itr != end();
                ++itr)
            {
                nodePath.push_back(const_cast<crNode*>(itr->get()));
            }
            
            return nodePath;
        }
        
        /** Check the validity of the RefNodePath to ensure that the parent path
          * matches those availble in the leaf node of the path.*/
        bool valid() const
        {
            // an empty NodePaath is invalid.
            if (empty()) return false;
        
            // check to make sure that this RefNodeList isn't the only
            // place that the nodes are referenced, if one node has
            // a ref count of 1 then nodes must have been removed 
            // from the scene graph elsewhere invalidating this RefNodePath.
            for(const_iterator itr=begin();
                itr != end();
                ++itr)
            {
                if ((*itr)->referenceCount()<=1) return false;
            }
            
            const_reverse_iterator ritr=rbegin();
            const CRCore::crNode* node = ritr->get();
            ++ritr;
            while (ritr!=rend())
            {
                const CRCore::crNode* parent = ritr->get();
                // search of parent in current nodes parent list
                const CRCore::crNode::ParentArray& parents = node->getParents();
                CRCore::crNode::ParentArray::const_iterator pitr=parents.begin();
                for(; pitr!=parents.end() && parent!=*pitr; ++pitr) {}
                if (pitr==parents.end()) 
                {
                    // original parent not found, so linkage must have changed
                    // invalidating this RefNodePath.
                    return false;
                }

                node = parent;                
                ++ritr;
            }
            
            // we've passed all the test that could invalidate this RefNodePath
            return true;
     }
    
};

} // namespace

#endif

