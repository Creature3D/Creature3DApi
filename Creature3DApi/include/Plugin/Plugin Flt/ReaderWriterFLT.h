
//
// OpenFlight?loader for Open Scene Graph
//
//  Copyright (C) 2000  Brede Johansen
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//  The Open Scene Graph (OSG) is a cross platform C++/OpenGL library for 
//  real-time rendering of large 3D photo-realistic models. 
//  The OSG homepage is http://www.openscenegraph.org/
//
//  MultiGen, OpenFlight, and Flight Format are registered trademarks of MultiGen Inc.
//

#ifndef __FLT_READER_WRITER_FLT_H
#define __FLT_READER_WRITER_FLT_H



#include <string>

#include <CRCore/crBase.h>
#include <CRCore/crNode.h>

#include <CRIOManager/crRegistry.h>
#include <CRIOManager/crFileNameUtils.h>
#include <CRIOManager/crReentrantMutex.h>

namespace flt {


class ReaderWriterFLT : public CRIOManager::crReaderWriter
{
public:

    virtual const char* className() { return "FLT Reader/Writer"; }
    virtual bool acceptsExtension(const std::string& extension) const
    {
        return CRIOManager::equalCaseInsensitive(extension,"flt")|CRIOManager::equalCaseInsensitive(extension,"cr");
    }

    virtual ReadResult readObject(const std::string& fileName, const CRIOManager::crReaderWriter::Options*) const;
    virtual ReadResult readNode(const std::string& fileName, const CRIOManager::crReaderWriter::Options*) const;

protected:
	mutable CRIOManager::crReentrantMutex _serializerMutex;

};


}; // end namespace flt

#endif // __FLT_CONTROL_RECORD_H


