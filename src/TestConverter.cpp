#include "TestConverter.hpp"
#include <fstream>

SDefaultTestSpec convertFormTestToDefault(const std::string &path_, const std::string &testFileName_)
{
    SDefaultTestSpec emulatedTestFiles;
    emulatedTestFiles.in = std::string("emulated/") + testFileName_ + std::string(".in");
    emulatedTestFiles.out = std::string("emulated/") + testFileName_ + std::string(".out");


    std::ifstream testFile(path_ + testFileName_);
    if (!testFile.is_open())
        throw (std::string("convertFormTestToDefault:Can't open:") + path_ + testFileName_);

    createDir(path_ + std::string("emulated/"));
    std::ofstream inOut(path_ + emulatedTestFiles.in), outOut(path_ + emulatedTestFiles.out);
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
        throw (std::string("convertFormTestToDefault:No output provided in .test file:") + testFileName_);
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
