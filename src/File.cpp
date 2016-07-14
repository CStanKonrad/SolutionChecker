#include "File.hpp"
//#include <iostream>

void CFile::openDir(std::string dirPath_)
{
    dirPath_ += ".";
    directory = opendir(dirPath_.c_str());

    if (directory == nullptr)
        throw (std::string("CFile::openDir: Can't open directory: ") + dirPath_);
}

void CFile::closeDir()
{
    closedir(directory);
    return;
}

std::string CFile::nextFile()
{
    if (directory == nullptr)
        throw "CFile::nextFile: Directory not opened";

    dirElement = readdir(directory);

    if (dirElement == nullptr)
        return std::string("");
    else
        return std::string(dirElement->d_name);
}


std::string readLine(std::ifstream &in_)
{
    std::string result = "";
    while (in_.peek() != '\n' && in_.eof() == false)
    {
        result += in_.get();
    }
    in_.get();
    return result;
}

void createDir(std::string dir_)
{
    CFile dir;
    try
    {
        dir.openDir(dir_);
    }
    catch (std::string _bug)
    {
        //std::cout << "Creating: " << toDir_ << std::endl;
        system((std::string("mkdir \"") + dir_ + std::string("\"")).c_str());
    }
}

void copyFile(std::string from_, std::string toDir_, std::string toFile_)
{
    createDir(toDir_);
    system((std::string("cat \"") + from_ + std::string("\" > \"") +  toDir_ + toFile_ + std::string("\"")).c_str());
}

