#include "Checker.hpp"
#include "File.hpp"
#include "Time.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

std::string createFullPath(const SSettings &_settings)
{
    std::string result = "tasks/";
    result += _settings.taskName;
    result += "/";
    result += _settings.subFolder;
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
    std::string fullPath = createFullPath(_settings);
    CFile dirBrowser;
    dirBrowser.openDir(fullPath);

    std::string fileNameBufIn = dirBrowser.nextFile();
    std::string fileNameBufOut;


    std::vector <std::string> inputNames;
    while (fileNameBufIn.size() > 0)
    {
        inputNames.push_back(fileNameBufIn);
        fileNameBufIn = dirBrowser.nextFile();
    }
    if (_settings.checkOrder == ECheckOrder::ALPHABETICAL)
    {
        std::sort(inputNames.begin(), inputNames.end());
    }

    int sysReturnVal;
    for (unsigned int i = 0; i < inputNames.size(); i++)
    {
        fileNameBufIn = inputNames[i];

        if (strcmp(&fileNameBufIn[fileNameBufIn.size() - 3], ".in") == 0)
        {
            stoper.begin();
            system((_settings.runPrefix + std::string("\"") + _settings.taskName + std::string("\" < \"") + fullPath + fileNameBufIn + std::string("\" > tmp/tested.out")).c_str());
            stoper.end();

            fileNameBufOut = makeOutFromIn(fileNameBufIn);

            std::cout << fileNameBufIn << ": ";
            std::cout << stoper.getTimeString() << " ";

            sysReturnVal = system((std::string("\"") + _settings.cmpFunction + std::string("\" ") + _settings.cmpOptions + std::string(" \"") + fullPath + fileNameBufOut + std::string("\"  tmp/tested.out")).c_str());
            std::cout << ( sysReturnVal == 0 ? _settings.okMessage : _settings.waMessage) << std::endl;

            if (sysReturnVal != 0 && _settings.waStop == true)
            {
                return;
            }
        }
    }

}
