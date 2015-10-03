#include "TestConverter.hpp"
#include <fstream>

SDefaultTestSpec convertFormTestToDefault(const std::string &_path, const std::string &_testFileName)
{
    SDefaultTestSpec emulatedTestFiles;
    emulatedTestFiles.in = std::string("emulated/") + _testFileName + std::string(".in");
    emulatedTestFiles.out = std::string("emulated/") + _testFileName + std::string(".out");


    std::ifstream testFile(_path + _testFileName);
    if (!testFile.is_open())
        throw (std::string("convertFormTestToDefault:Can't open:") + _path + _testFileName);

    createDir(_path + std::string("emulated/"));
    std::ofstream inOut(_path + emulatedTestFiles.in), outOut(_path + emulatedTestFiles.out);
    if (inOut.is_open() == false || outOut.is_open() == false)
        throw (std::string("convertFormTestToDefault:Can't create emulated files") + emulatedTestFiles.in + std::string(" ") + emulatedTestFiles.out);

    std::string buffer;
    buffer = readLine(testFile);
    while (buffer != "~e0!~" && testFile.eof() == false)
    {
        inOut << buffer << std::endl;
        buffer = readLine(testFile);
    }
    if (testFile.eof() == true)
        throw (std::string("convertFormTestToDefault:No output provided in .test file:") + _testFileName);
    do
    {
        buffer = readLine(testFile);
        outOut << buffer << std::endl;
    } while (testFile.eof() == false);

    testFile.close();
    inOut.close();
    outOut.close();
    return emulatedTestFiles;
}
