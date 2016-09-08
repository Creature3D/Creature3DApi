/* dxfReader for OpenSceneGraph  Copyright (C) 2005 by GraphArchitecture ( grapharchitecture.com )
 * Programmed by Paul de Repentigny <pdr@grapharchitecture.com>
 * 
 * OpenSceneGraph is (C) 2004 Robert Osfield
 * 
 * This library is provided as-is, without support of any kind.
 *
 * Read DXF docs or OSG docs for any related questions.
 * 
 * You may contact the author if you have suggestions/corrections/enhancements.
 */
#include <CRIOManager/crRegistry>
#include <CRIOManager/ReadFile>
#include <CRIOManager/FileUtils>
#include <CRIOManager/FileNameUtils>

#include <map>
#include <iostream>
#include <utility>

#include <string>
#include <sstream>
#include <string.h>

#include "dxfFile.h"
#include "crDXFWritercrNodeVisitor.h"

using namespace CRCore;
using namespace CRIOManager;
using namespace std;


class ReaderWriterdxf : public CRIOManager::crReaderWriter
{
public:
    ReaderWriterdxf()
    {
        supportsExtension("dxf","Autodesk DXF format");
    }
    
    virtual const char* className() { return "Autodesk DXF Reader/Writer"; }
    virtual ReadResult readNode(const std::string& fileName, const CRIOManager::crReaderWriter::Options*) const;


    virtual WriteResult writeObject(const CRCore::crBase& obj,const std::string& fileName,const Options* options=NULL) const 
    {
        const CRCore::crNode* node = dynamic_cast<const CRCore::crNode*>(&obj);
        if (node)
            return writecrNode(*node, fileName, options);
        else 
            return WriteResult(WriteResult::FILE_NOT_HANDLED); 
    }
    
    
    virtual WriteResult writeObject(const CRCore::crBase& obj,std::ostream& fout,const Options* options=NULL) const 
    {
        const CRCore::crNode* node = dynamic_cast<const CRCore::crNode*>(&obj);
        if (node)
            return writecrNode(*node, fout, options);
        else 
            return WriteResult(WriteResult::FILE_NOT_HANDLED); 
    }

    virtual WriteResult writecrNode(const CRCore::crNode& node,std::ostream& fout,const Options* =NULL) const 
    {         

        
        crDXFWritercrNodeVisitor nv(fout); 

        (const_cast<CRCore::crNode*>(&node))->accept(nv); // first pass is to get all node names and types -> layers

        if ( nv.writeHeader(node.getBound()) ) {
            (const_cast<CRCore::crNode*>(&node))->accept(nv);  // second pass outputs data
            nv.writeFooter();
        }
    
        return WriteResult(WriteResult::FILE_SAVED); 
    }

    virtual WriteResult writecrNode(const CRCore::crNode& node,const std::string& fileName,const Options* options =NULL) const 
    { 
        if (!acceptsExtension(CRIOManager::getFileExtension(fileName)))
            return WriteResult(WriteResult::FILE_NOT_HANDLED);

        CRIOManager::ofstream f(fileName.c_str());
        
        if (!f.is_open() ) {
            return WriteResult(WriteResult::ERROR_IN_WRITING_FILE);
        }
        crDXFWritercrNodeVisitor nv(f); 
                
        (const_cast<CRCore::crNode*>(&node))->accept(nv); // first pass is to get all node names and types -> layers

        if ( nv.writeHeader(node.getBound()) ) {
            (const_cast<CRCore::crNode*>(&node))->accept(nv);  // second pass outputs data
            nv.writeFooter();
        }

        return WriteResult(WriteResult::FILE_SAVED); 
    }

protected:
};

// register with crRegistry to instantiate the above reader/writer.
REGISTER_OSGPLUGIN(dxf, ReaderWriterdxf)


// read file and convert to OSG.
CRIOManager::crReaderWriter::ReadResult 
ReaderWriterdxf::readNode(const std::string& filename, const CRIOManager::crReaderWriter::Options* options) const
{
    std::string ext = CRIOManager::getFileExtension(filename);
    if (!acceptsExtension(ext)) return ReadResult::FILE_NOT_HANDLED;

    // extract accuracy options if available
    if (options) {
        bool useAccuracy=false;  // if we specify accuracy of curve rendering or not
        double maxError=0.0;     // if useAccuracy - the accuracy (max deviation) from the arc
        bool improveAccuracyOnly=false; // if true only use the given accuracy if it would improve the curve compared to the previous implementation
                                        // Thus you can ensure that large curves get rendered better but small ones don't get worse
        
        std::string optionsstring=options->getOptionString();
        
        size_t accstart=optionsstring.find("Accuracy(");
        if (accstart>=0) {
            const char* start=optionsstring.c_str() + accstart + strlen("Accuracy(");
            if (sscanf(start,"%lf",&maxError)==1) useAccuracy=true;
        }
        if (useAccuracy) {
            // Option to only use the new accuracy code when it would improve on the accuracy of the old method
            if (optionsstring.find("ImproveAccuracyOnly") != std::string::npos) {
                improveAccuracyOnly=true;
            } 
            // Pull out the initial dxfArc copy from the registry and set accuracy there. 
            // When actual dxfArcs/Circles are created they will inherit these parameters from the exemplar
            dxfEntity::getcrRegistryEntity("ARC")->setAccuracy(true,maxError,improveAccuracyOnly);
            dxfEntity::getcrRegistryEntity("CIRCLE")->setAccuracy(true,maxError,improveAccuracyOnly); 
        } // accuracy options exists
    } // options exist


    // Open
    dxfFile df(filename);
    if (df.parseFile()) {
        // convert to OSG
        CRCore::crGroup* CRCore_top = df.dxf2CRCore();
        return (CRCore_top);
    }
    return ReadResult::FILE_NOT_HANDLED;
}

