#include "Checker.hpp"
#include "File.hpp"
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
    //result += _settings.testSubFolder;
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
    dirBrowser.openDir(fullPath + _settings.testSubFolder);

    std::string fileNameBufIn = dirBrowser.nextFile();
    std::string fileNameBufOut;

    if (_settings.testName.size() > 0)
    {
        fileNameBufIn = _settings.testName;
        fileNameBufOut = makeOutFromIn(fileNameBufIn);

        checkTest(_settings, stoper, fullPath, fileNameBufIn, fileNameBufOut);
        return;
    }

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

    SCheckResult checkResult;
    for (unsigned int i = 0; i < inputNames.size(); i++)
    {
        fileNameBufIn = inputNames[i];

        if (strcmp(&fileNameBufIn[fileNameBufIn.size() - 3], ".in") == 0)
        {
			fileNameBufOut = makeOutFromIn(fileNameBufIn);

            checkResult = checkTest(_settings, stoper, fullPath, fileNameBufIn, fileNameBufOut);

            if (checkResult.cmpReturnVal != int(checkResult.ECmpRet::OK) && _settings.waStop == true)
				return;
        }
    }

}
SCheckResult checkTest(const SSettings &_settings, CStoper &_stoper, const std::string &_fullPath, const std::string &_inputFile, const std::string &_outputFile)
{
	SCheckResult result;
	_stoper.begin();
	result.solutionReturnVal = system(((_settings.limits.memoryLimitArguments.size() != 0 ? _settings.limits.memoryLimitFunctionName + std::string (" ") + _settings.limits.memoryLimitArguments + std::string("\n") : std::string(""))
	 + (_settings.limits.timeLimitArguments.size() != 0 ?  _settings.limits.timeLimitFunctionName + std::string (" ") + _settings.limits.timeLimitArguments + std::string (" ") : std::string (""))
	 + _settings.runPrefix + std::string("\"") + _fullPath + _settings.solutionSubFolder + _settings.taskName + std::string("\" < \"") + _fullPath + _settings.testSubFolder +  _inputFile + std::string("\" > tmp/tested.out")
   ).c_str());
	_stoper.end();

	std::cout << _inputFile << ": ";
	std::cout << _stoper.getTimeString() << " ";
	std::cout << "r: " << result.solutionReturnVal << " ";

	result.cmpReturnVal = system((std::string("\"") + _settings.cmpFunction + std::string("\" ") + _settings.cmpOptions + std::string(" \"") + _fullPath + _settings.testSubFolder +  _outputFile + std::string("\"  tmp/tested.out")).c_str());
	if (result.cmpReturnVal != int(result.ECmpRet::OK) && _settings.waSave == true)
	{
        copyFile("tmp/tested.out", _fullPath + _settings.testSubFolder + std::string("solution.wa/"), _outputFile);
	}
	std::cout << (result.solutionReturnVal == int(result.ESolRet::OK) ? "" : _settings.errorMessage + std::string(" "));
    std::cout << (result.cmpReturnVal == int(result.ECmpRet::OK) ? _settings.okMessage : _settings.waMessage) << std::endl;
	return result;
}
