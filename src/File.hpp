#ifndef CSTANKONRAD_SOLUTIONCHECKER_FILE_HPP_INCLUDED
#define CSTANKONRAD_SOLUTIONCHECKER_FILE_HPP_INCLUDED

#include <string>
#include <fstream>

#include <dirent.h>

class CFile
{
private:
    DIR *directory = nullptr;
    dirent *dirElement = nullptr;
public:
    /* return true if directory can be opened else false */
    void openDir(std::string dirPath_);  // for example "my/directory/" will enable browsing files from this directory
    void closeDir();

    /* nextFile()
    * return next file or directory name if exists or void string if doesn't exist
    * throws "CFile::nextFile: Directory not opened"
    */
    std::string nextFile();
};

/* read characters to string while (next_character != new_line) and read new_line (but not to string) */
std::string readLine(std::ifstream &in_);
/* If no directory named _dir exists create one */
void createDir(std::string dir_);
/* copy content from _from to _toDir/_toFile */
void copyFile(std::string from_, std::string toDir_, std::string toFile_);


#endif // CSTANKONRAD_SOLUTIONCHECKER_FILE_HPP_INCLUDED
