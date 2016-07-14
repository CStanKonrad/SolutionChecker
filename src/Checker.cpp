#include "Checker.hpp"
#include "File.hpp"
#include "TestConverter.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::string makeOutFromIn(const std::string &_inFileName)
{
    std::string result = _inFileName;
    result.pop_back();
    result.pop_back();

    result += "out";
    return result;

}

bool isSuffix(const std::string &_str, const std::string &_suffixCandidate)
{
    if (_str.size() > _suffixCandidate.size())
    {
        unsigned int suffixBeg = _str.size() - _suffixCandidate.size();
        for (unsigned int i = suffixBeg; i < _str.size(); i++)
        {
            if (_str[i] != _suffixCandidate[i - suffixBeg])
                return false;
        }
    }
    else
        return false;
    return true;
}


bool solSortAlphabetical(const std::string &_a, const std::string &_b)
{
    if (_a.size() < _b.size())
        return true;
    else if (_a.size() > _b.size())
        return false;
    else
    {
        for (unsigned int i = 0; i < _a.size(); i++)
        {
            if (_a[i] < _b[i])
                return true;
            else if (_a[i] == _b[i])
                continue;
            else
                return false;
        }
    }
    return false;
}

bool askForTermination(const SSettings &_settings)    //true = terminate; false = don't terminate
{
    std::string tmp;
    std::cout << _settings.terminationAskMessage;
    std::cin >> tmp;
    if (tmp == "y" || tmp == "Y")
        return true;
    else if (tmp == "n" || tmp == "N")
        return  false;
    else
    {
        throw (std::string("shouldCheckingBeTerminated: Wrong input: expected y, Y, n or N readed:") + tmp);
    }
}

bool shouldCheckingBeTerminated(const SSettings &_settings, const SCheckResult &_checkResult)
{

    if (_checkResult.solutionReturnVal != int(SCheckResult::ESolRet::OK))
    {
        if (_settings.noClearStop == true || ((_checkResult.solutionReturnVal == int(SCheckResult::ESolRet::TLE)) && (_settings.tleStop == true)) ||
            ((_checkResult.solutionReturnVal != int(SCheckResult::ESolRet::TLE)) && (_settings.errStop == true)))
        {
            if (_settings.terminateAsk == true)
            {
                return askForTermination(_settings);
            }
            else
            {
                return true;
            }
        }
    }
    else if (_checkResult.cmpReturnVal != int(SCheckResult::ECmpRet::OK))
    {
        if (_settings.noClearStop == true || _settings.waStop)
        {
            if (_settings.terminateAsk == true)
            {
                return askForTermination(_settings);
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}

void updateCheckStats(SCheckStatistics &_stats, const SCheckResult &_result)
{

    if (_result.solutionReturnVal != int(SCheckResult::ESolRet::OK))
    {
        if (_result.solutionReturnVal == int(SCheckResult::ESolRet::TLE))
            _stats.numOfTLE++;
        else if (_result.solutionReturnVal != int(SCheckResult::ESolRet::OK))
            _stats.numOfErrors++;
    }
    else if (_result.cmpReturnVal != int(SCheckResult::ECmpRet::OK))
    {
        if (_result.cmpReturnVal != int(SCheckResult::ECmpRet::OK))
            _stats.numOfWA++;
    }
    else
    {
        _stats.numOfOK++;
    }
    _stats.numOfTests++;
}


void checkSolution(const SSettings &_settings)
{
    switch(_settings.checkType)
    {
    case ECheckType::DIFF:
        checkDiff(_settings);
        break;
    case ECheckType::GENERATE:
        checkGenerate(_settings);
        break;
    default:
        throw "checkSolution: Sorry but that option isn't available";
        break;
    }
    return;
}

void displayCheckInfoBegin(const SSettings &_settings, const std::string &_fullpath)
{
    std::cout << _settings.checkingStartMessage << std::endl;
    std::cout << std::endl;
    std::cout << _settings.string_Main_pathd << _fullpath << std::endl;
    std::cout << _settings.string_Solutiond << _settings.solutionSubFolder + _settings.solutionName << std::endl;
    std::cout << _settings.string_Patternd << _settings.pattern << std::endl;
    std::cout << _settings.string_Test_folderd << _settings.testSubFolder << std::endl;
    std::cout << std::endl;
}

void displayCheckSummary(const SSettings &_settings, const SCheckStatistics &_checkStats)
{
    std::cout << "----Summary----" << std::endl;

    if (_checkStats.numOfWA != 0 || _checkStats.numOfErrors != 0 || _checkStats.numOfTLE != 0)
    {
        std::cout << _settings.color_attention << "!!!!!!!!!!!!!" << _settings.color_reset << std::endl;

        std::cout << _settings.color_attention << "!!!WARNING!!!" << _settings.color_reset << " you have at least one " << _settings.waMessage << ", "
        << _settings.errorMessage << " or " << _settings.tleMessage << std::endl;

        std::cout << _settings.color_attention << "!!!!!!!!!!!!!" << _settings.color_reset << std::endl;
    }

    std::cout << "Tests:" << _checkStats.numOfTests << " "
    << _settings.okMessage << ":" << _checkStats.numOfOK  << " "
    << _settings.waMessage << ":" << _checkStats.numOfWA << " "
    << _settings.errorMessage << ":" << _checkStats.numOfErrors << " "
    << _settings.tleMessage << ":" << _checkStats.numOfTLE << " "
    << "seed:" << _settings.generatorSeed <<
     std::endl;
    std::cout << "---------------" << std::endl;
    std::cout.flush();
}

void checkGenerate(const SSettings &_settings)
{
    CStoper stoper;
    std::string fullPath = createFullPath(_settings);
    displayCheckInfoBegin(_settings, fullPath);

    createDir(fullPath + _settings.testSubFolder);

    std::string inputFile;
    std::string outputFile;

    int generatorReturnValue = _settings.generatorSeed;
    SCheckResult checkResult;
    SCheckStatistics checkStats;
    for (int i = 1; i <= _settings.generatorNumOfCalls; i++)
    {
        inputFile = (_settings.testName.size() == 0 ? std::to_string(i) + std::string(".in"): _settings.testName);
        system((_settings.generatorRunPrefix + std::string("\"") + fullPath + _settings.generatorName + std::string("\"") + std::string(" ") + std::to_string(generatorReturnValue)
        + std::string(" ") + _settings.generatorOptions + std::string(" > ") + std::string("\"") + fullPath + _settings.testSubFolder + inputFile + std::string("\"")).c_str());

        generatorReturnValue++;

        if (_settings.pattern.size() != 0)
        {
            outputFile = makeOutFromIn(inputFile);
            system((_settings.patternRunPrefix + std::string("\"") + fullPath + _settings.pattern + std::string("\" < \"") + fullPath + _settings.testSubFolder +  inputFile + std::string("\" > \"")
            + fullPath + _settings.testSubFolder +  outputFile + std::string("\"")).c_str());

            checkResult = checkTest(_settings, stoper, fullPath, inputFile, outputFile, std::string("\033[0m"), i);

            updateCheckStats(checkStats, checkResult);

            if (shouldCheckingBeTerminated(_settings, checkResult) == true)
                break;
            /*if (checkResult.cmpReturnVal != int(checkResult.ECmpRet::OK) && _settings.waStop == true)
				break;
            if (checkResult.solutionReturnVal != int(checkResult.ESolRet::OK) && _settings.noClearStop == true)
                break;*/

        }

    }
    if (_settings.pattern.size() != 0)
    {
        displayCheckSummary(_settings, checkStats);
        /*std::cout << "----Summary----" << std::endl;
        std::cout << "Tests:" << checkStats.numOfTests << " "
        << _settings.okMessage << ":" << checkStats.numOfOK  << " "
        << _settings.waMessage << ":" << checkStats.numOfWA << " "
        << _settings.errorMessage << ":" << checkStats.numOfErrors << " "
        << _settings.tleMessage << ":" << checkStats.numOfTLE << " "
        << "seed:" << _settings.generatorSeed <<
         std::endl;
        std::cout << "---------------" << std::endl;
        std::cout.flush();*/
    }
}


void checkDiff(const SSettings &_settings)
{
    CStoper stoper;
    std::string fullPath = createFullPath(_settings);

    displayCheckInfoBegin(_settings, fullPath);

    CFile dirBrowser;
    dirBrowser.openDir(fullPath + _settings.testSubFolder);

    SDefaultTestSpec fileNameBuf;
    fileNameBuf.in = dirBrowser.nextFile();

    std::vector <std::string> inputNames;
    if (_settings.testName.size() > 0)
        inputNames.push_back(_settings.testName);
    else
    {
        while (fileNameBuf.in.size() > 0)
        {
            inputNames.push_back(fileNameBuf.in);
            fileNameBuf.in = dirBrowser.nextFile();
        }
    }
    if (_settings.checkOrder == ECheckOrder::ALPHABETICAL)
    {
        std::sort(inputNames.begin(), inputNames.end(), solSortAlphabetical);
    }

    SCheckResult checkResult;
    SCheckStatistics checkStats;
    for (unsigned int i = 0; i < inputNames.size(); i++)
    {
        fileNameBuf.in = inputNames[i];

        if (isSuffix(fileNameBuf.in, std::string(".in")) == true)
        {
			fileNameBuf.out = makeOutFromIn(fileNameBuf.in);

            checkResult = checkTest(_settings, stoper, fullPath, fileNameBuf.in, fileNameBuf.out, std::string("\033[0m"));

            updateCheckStats(checkStats, checkResult);

            if (shouldCheckingBeTerminated(_settings, checkResult) == true)
                break;
        }
        else if (isSuffix(fileNameBuf.in, std::string(".test")) == true)
        {
            fileNameBuf = convertFormTestToDefault(fullPath + _settings.testSubFolder, fileNameBuf.in);

            checkResult = checkTest(_settings, stoper, fullPath, fileNameBuf.in, fileNameBuf.out, std::string("\033[1;36m"));

            updateCheckStats(checkStats, checkResult);

            if (shouldCheckingBeTerminated(_settings, checkResult) == true)
                break;
        }
    }
    displayCheckSummary(_settings, checkStats);
    /*std::cout << "----Summary----" << std::endl;
    std::cout << "Tests:" << checkStats.numOfTests << " "
    << _settings.okMessage << ":" << checkStats.numOfOK  << " "
    << _settings.waMessage << ":" << checkStats.numOfWA << " "
    << _settings.errorMessage << ":" << checkStats.numOfErrors << " "
    << _settings.tleMessage << ":" << checkStats.numOfTLE <<
     std::endl;
    std::cout << "---------------" << std::endl;
    std::cout.flush();*/

}
SCheckResult checkTest(const SSettings &_settings, CStoper &_stoper, const std::string &_fullPath, const std::string &_inputFile, const std::string &_outputFile, const std::string &_testNameColor, const int _testNumber)
{
	SCheckResult result;
	_stoper.begin();
	result.solutionReturnVal = system(((_settings.limits.memoryLimitArguments.size() != 0 ? _settings.limits.memoryLimitFunctionName + std::string (" ") + _settings.limits.memoryLimitArguments + std::string("\n") : std::string(""))
	 + (_settings.limits.timeLimitArguments.size() != 0 ?  _settings.limits.timeLimitFunctionName + std::string (" ") + _settings.limits.timeLimitArguments + std::string (" ") : std::string (""))
	 + _settings.solutionRunPrefix + std::string("\"") + _fullPath + _settings.solutionSubFolder + _settings.solutionName + std::string("\" < \"") + _fullPath + _settings.testSubFolder +  _inputFile + std::string("\" > tmp/tested.out")
   ).c_str());
	_stoper.end();

    if (_settings.checkType == ECheckType::GENERATE && _settings.testName.size() > 0)
    {
        std::cout << "#";
        std::cout.width(2);
        std::cout << std::left << _testNumber << " ";
    }

    if (_settings.isColorOutputEnabled == true)
        std::cout << _testNameColor;
	std::cout << _inputFile << ": ";
	if (_settings.isColorOutputEnabled == true)
        std::cout << "\033[0m";
	std::cout << _stoper.getTimeString() << " ";
	std::cout << "r: " << result.solutionReturnVal << " ";

	result.cmpReturnVal = system((std::string("\"") + _settings.cmpFunction + std::string("\" ") + _settings.cmpOptions + std::string(" \"") + _fullPath + _settings.testSubFolder +  _outputFile + std::string("\"  tmp/tested.out")).c_str());
	if (result.cmpReturnVal != int(SCheckResult::ECmpRet::OK) && _settings.waSave == true)
	{
        std::string copiedTestPrefix;
        if (_settings.checkType == ECheckType::GENERATE && _settings.testName.size() > 0)
            copiedTestPrefix = std::to_string(_testNumber) + std::string("::");
        else
            copiedTestPrefix = "";

        copyFile("tmp/tested.out", _fullPath + _settings.testSubFolder + std::string("solution.wa/"), copiedTestPrefix + _outputFile + std::string(".wa"));
        copyFile(_fullPath + _settings.testSubFolder +  _inputFile, _fullPath + _settings.testSubFolder + std::string("solution.wa/"), copiedTestPrefix + _inputFile);
        copyFile(_fullPath + _settings.testSubFolder +  _outputFile, _fullPath + _settings.testSubFolder + std::string("solution.wa/"), copiedTestPrefix + _outputFile);
	}
	if (result.solutionReturnVal != int(SCheckResult::ESolRet::OK))
	{
        if (result.solutionReturnVal == int(SCheckResult::ESolRet::TLE))
            std::cout << _settings.tleMessage + std::string(" ");
        else
            std::cout << _settings.errorMessage + std::string(" ");

        std::cout << std::endl;
	}
	else
    {
        std::cout << (result.cmpReturnVal == int(SCheckResult::ECmpRet::OK) ? _settings.okMessage : _settings.waMessage) << std::endl;
    }
    std::cout.flush();
	return result;
}
