#include "File.hpp"
//#include <iostream>

void CFile::openDir(std::string _dirPath)
{
    _dirPath += ".";
    directory = opendir(_dirPath.c_str());

    if (directory == nullptr)
        throw (std::string("CFile::openDir: Can't open directory: ") + _dirPath);
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


std::string readLine(std::ifstream &_in)
{
    std::string result = "";
    while (_in.peek() != '\n' && _in.eof() == false)
    {
        result += _in.get();
    }
    _in.get();
    return result;
}

void createDir(std::string _dir)
{
    CFile dir;
    try
    {
        dir.openDir(_dir);
    }
    catch (std::string _bug)
    {
        //std::cout << "Creating: " << _toDir << std::endl;
        system((std::string("mkdir \"") + _dir + std::string("\"")).c_str());
    }
}

void copyFile(std::string _from, std::string _toDir, std::string _toFile)
{
    createDir(_toDir);
    system((std::string("cat \"") + _from + std::string("\" > \"") +  _toDir + _toFile + std::string("\"")).c_str());
}

