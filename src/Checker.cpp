#include "Checker.hpp"
#include "File.hpp"
#include "Time.hpp"
#include <string>
#include <cstring>
#include <iostream>

std::string createFullPath(const std::string &_taskName)
{
    std::string result = "tasks/";
    result += _taskName;
    result += "/";
    return result;
}

std::string makeOutFromIn(const std::string &_inFileName)
{
    std::string result = _inFileName;
    result.pop_back();
    result.pop_back();

    result += "out";
    return result;

}

void checkSolution(const SSettings &_settings)
{
    switch(_settings.checkType)
    {
    case ECheckType::DIFF:
        checkDiff(_settings);
        break;
    default:
        throw "checkSolution: Sorry but that option isn't available";
        break;
    }
    return;
}

void checkDiff(const SSettings &_settings)
{
    CStoper stoper;
    std::string fullPath = createFullPath(_settings.taskName);
    CFile dirBrowser;
    dirBrowser.openDir(fullPath);

    std::string fileNameBufIn = dirBrowser.nextFile();
    std::string fileNameBufOut;
    while (fileNameBufIn.size() > 0)
    {
        if (strcmp(&fileNameBufIn[fileNameBufIn.size() - 3], ".in") == 0)
        {
            stoper.begin();
            system((std::string("./\"") + _settings.taskName + std::string("\" < \"") + fullPath + fileNameBufIn + std::string("\" > tmp/tested.out")).c_str());
            stoper.end();

            fileNameBufOut = makeOutFromIn(fileNameBufIn);
            std::cout << fileNameBufIn << ": ";
            std::cout << stoper.getTimeString() << " " << (system((std::string("\"") + _settings.cmpFunction + std::string("\" ") + _settings.cmpOptions + std::string(" \"") + fullPath + fileNameBufOut + std::string("\"  tmp/tested.out")).c_str()) == 0 ? _settings.okMessage : _settings.waMessage) << std::endl;
        }

        fileNameBufIn = dirBrowser.nextFile();
    }

}
