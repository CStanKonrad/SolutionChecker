#ifndef CSTANKONRAD_TASKCHECKER_FILE_HPP_INCLUDED
#define CSTANKONRAD_TASKCHECKER_FILE_HPP_INCLUDED

#include <string>

#include <dirent.h>

class CFile
{
private:
    DIR *directory = nullptr;
    dirent *dirElement = nullptr;
public:
    /* return true if directory can be opened else false */
    void openDir(std::string _dirPath);  // for example "my/directory/" will enable browsing files from this directory
    void closeDir();

    /* nextFile()
    * return next file or directory name if exists or void string if doesn't exist
    * throws "CFile::nextFile: Directory not opened"
    */
    std::string nextFile();
};


#endif // CSTANKONRAD_TASKCHECKER_FILE_HPP_INCLUDED
