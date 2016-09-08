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
#ifndef CRIOMANAGER_FILEUTILS
#define CRIOMANAGER_FILEUTILS 1

#include <CRIOManager/crRegistry.h>

#include <vector>
#include <deque>
#include <string>


namespace CRIOManager {

enum CaseSensitivity
{
    CASE_SENSITIVE,
    CASE_INSENSITIVE,
};

enum FileType
{
    FILE_NOT_FOUND,
    REGULAR_FILE,
    DIRECTORY,
};

extern CRIOMANAGER_EXPORT bool copyFile(const std::string &srcFile, const std::string &destFile );

// Make a new directory.  Returns true if directory exists or was created.
extern CRIOMANAGER_EXPORT bool makeDirectory( const std::string &directoryPath );

// Make a new directory for a given file.
extern CRIOMANAGER_EXPORT bool makeDirectoryForFile( const std::string &filePath );
    
extern CRIOMANAGER_EXPORT bool removeDirectory( const std::string &directoryPath );

/** return true if a file exisits. */
extern CRIOMANAGER_EXPORT bool fileExists(const std::string& filename);

/** return type of file. */
extern CRIOMANAGER_EXPORT FileType fileType(const std::string& filename);

/** find specified file in specified file path.*/
extern CRIOMANAGER_EXPORT std::string findFileInPath(const std::string& filename, const FilePathList& filePath,CaseSensitivity caseSensitivity=CASE_SENSITIVE);

/** return the directory/filename of a file if its is contained within specified directory.
  * return "" if directory does not contain file.  If caseInsensitive is set to true then
  * a case insensitive comparison is used to compare fileName to directory contents.
  * This is useful when unix programs attempt read case insentive windows filenames.
  */
extern CRIOMANAGER_EXPORT std::string findFileInDirectory(const std::string& fileName,const std::string& dirName,CaseSensitivity caseSensitivity=CASE_SENSITIVE);

/** simple list of names to represent a directory's contents. */
typedef std::vector<std::string> DirectoryContents;

/** return the contents of a directory.
  * returns an empty array on any error.*/
extern CRIOMANAGER_EXPORT DirectoryContents getDirectoryContents(const std::string& dirName);



inline void setDataFilePathList(const FilePathList& filepath) { CRIOManager::crRegistry::instance()->setDataFilePathList(filepath); }

inline void setDataFilePathList(const std::string& paths) { CRIOManager::crRegistry::instance()->setDataFilePathList(paths); }

inline FilePathList& getDataFilePathList() { return CRIOManager::crRegistry::instance()->getDataFilePathList(); }

/** Search for specified file in file system, checking the DataFilePathList for possible paths, 
  * returning the full path of the first valid file found, return an empty string if no string is found.
  */
extern CRIOMANAGER_EXPORT std::string findDataFile(const std::string& filename,CaseSensitivity caseSensitivity=CASE_SENSITIVE);

/** Search for specified file in file system, checking first the database path set in the Options structure, then the DataFilePathList for possible paths, 
  * returning the full path of the first valid file found, return an empty string if no string is found.
  */
extern CRIOMANAGER_EXPORT std::string findDataFile(const std::string& filename,const crReaderWriter::Options* options, CaseSensitivity caseSensitivity=CASE_SENSITIVE);

inline void setLibraryFilePathList(const FilePathList& filepaths) { CRIOManager::crRegistry::instance()->setLibraryFilePathList(filepaths); }

inline void setLibraryFilePathList(const std::string& paths) { CRIOManager::crRegistry::instance()->setLibraryFilePathList(paths); }

inline FilePathList& getLibraryFilePathList() { return CRIOManager::crRegistry::instance()->getLibraryFilePathList(); }

extern CRIOMANAGER_EXPORT std::string findLibraryFile(const std::string& filename,CaseSensitivity caseSensitivity=CASE_SENSITIVE);

/** convert a string containing a list of paths  deliminated either with ';' (Windows) or ':' (All other platforms) into FilePath represetation.*/
extern CRIOMANAGER_EXPORT void convertStringPathIntoFilePathList(const std::string& paths,FilePathList& filepath);

extern CRIOMANAGER_EXPORT void appendPlatformSpecificLibraryFilePaths(FilePathList& filepath);
extern CRIOMANAGER_EXPORT void appendPlatformSpecificResourceFilePaths(FilePathList& filepath);

}

#endif