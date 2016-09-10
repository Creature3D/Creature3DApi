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
#ifndef CRCORE_FAST_BACK_STACK
#define CRCORE_FAST_BACK_STACK 1

#include <vector>

namespace CRCore {

/** Simple stack implementation that keeps the back() cached locally for fast access
  * rather than at the back of the vector which is the traditional stack implementation.
  * A conventional std::vector<> stores the rest of the stack. The fast_back_stack
  * although contains a stl container it only implments the back push_back(),pop_back()
  * and back() methods so is not as general purpose as stl stack implementation.
  * The focus of the fast_back_stack is purly to maximize the speed at which the
  * back can be accessed.*/
  
template<class T>
class fast_back_stack
{
    public:
    
        inline fast_back_stack():m_value(),_stack(),_size(0) {}

        inline fast_back_stack(const fast_back_stack& fbs):m_value(fbs.m_value),_stack(fbs._stack),_size(fbs._size) {}

        inline fast_back_stack(const T& value):m_value(value),_stack(),_size(1) {}

        fast_back_stack& operator = (const fast_back_stack& fbs)
        {
            m_value = fbs.m_value;
            _stack = fbs._stack;
            _size = fbs._size;
            return *this;
        }

        inline void clear() { _stack.clear(); _stack.reserve(_size); _size = 0; }

        inline bool empty() const { return _size==0; }

        inline unsigned int size() const { return _size; }

        inline T& back() { return m_value; }

        inline const T& back() const { return m_value; }

        inline void push_back()
        {
            if (_size>0)
            {
                _stack.push_back(m_value);
            }
            ++_size;
        }
        
        inline void push_back(const T& value)
        {
            if (_size>0)
            {
                _stack.push_back(m_value);
            }
            m_value = value;
            ++_size;
        }
        
        inline void pop_back()
        {
            if (_size>0)
            {
                if (!_stack.empty())
                {
                    m_value = _stack.back();
                    _stack.pop_back();
                }
                --_size;
            } // else error condition.
        }
        
        T              m_value;
        std::vector<T> _stack;
        unsigned int   _size;
};

}

#endif
