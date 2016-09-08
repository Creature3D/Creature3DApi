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
//Modified by 吴财华
#ifndef CRCORE_CRMATRIX_H
#define CRCORE_CRMATRIX_H 1

#include <CRCore/crMatrixd.h>
#include <CRCore/crMatrixf.h>

//#define CRCORE_USE_DOUBLE_MATRICES 1

namespace CRCore {

#ifdef CRCORE_USE_DOUBLE_MATRICES
    typedef crMatrixd crMatrix;
    typedef RefMatrixd RefMatrix;
#else
    typedef crMatrixf crMatrix;
    typedef RefMatrixf RefMatrix;

#endif

}


#endif