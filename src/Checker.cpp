#include "Checker.hpp"
#include "File.hpp"
#include "TestConverter.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::string makeOutFromIn(const std::string &inFileName_)
{
    std::string result = inFileName_;
    result.pop_back();
    result.pop_back();

    result += "out";
    return result;

}

bool isSuffix(const std::string &str_, const std::string &suffixCandidate_)
{
    if (str_.size() > suffixCandidate_.size())
    {
        unsigned int suffixBeg = str_.size() - suffixCandidate_.size();
        for (unsigned int i = suffixBeg; i < str_.size(); i++)
        {
            if (str_[i] != suffixCandidate_[i - suffixBeg])
                return false;
        }
    }
    else
        return false;
    return true;
}


bool solSortAlphabetical(const std::string &a_, const std::string &b_)
{
    if (a_.size() < b_.size())
        return true;
    else if (a_.size() > b_.size())
        return false;
    else
    {
        for (unsigned int i = 0; i < a_.size(); i++)
        {
            if (a_[i] < b_[i])
                return true;
            else if (a_[i] == b_[i])
                continue;
            else
                return false;
        }
    }
    return false;
}

bool askForTermination(const SSettings &settings_)    //true = terminate; false = don't terminate
{
    std::string tmp;
    std::cout << settings_.terminationAskMessage;
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

bool shouldCheckingBeTerminated(const SSettings &settings_, const SCheckResult &checkResult_)
{

    if (checkResult_.solutionReturnVal != int(SCheckResult::ESolRet::OK))
    {
        if (settings_.noClearStop == true || ((checkResult_.solutionReturnVal == int(SCheckResult::ESolRet::TLE)) && (settings_.tleStop == true)) ||
            ((checkResult_.solutionReturnVal != int(SCheckResult::ESolRet::TLE)) && (settings_.errStop == true)))
        {
            if (settings_.terminateAsk == true)
            {
                return askForTermination(settings_);
            }
            else
            {
                return true;
            }
        }
    }
    else if (checkResult_.cmpReturnVal != int(SCheckResult::ECmpRet::OK))
    {
        if (settings_.noClearStop == true || settings_.waStop)
        {
            if (settings_.terminateAsk == true)
            {
                return askForTermination(settings_);
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}

void updateCheckStats(SCheckStatistics &stats_, const SCheckResult &result_)
{

    if (result_.solutionReturnVal != int(SCheckResult::ESolRet::OK))
    {
        if (result_.solutionReturnVal == int(SCheckResult::ESolRet::TLE))
            stats_.numOfTLE++;
        else if (result_.solutionReturnVal != int(SCheckResult::ESolRet::OK))
            stats_.numOfErrors++;
    }
    else if (result_.cmpReturnVal != int(SCheckResult::ECmpRet::OK))
    {
        if (result_.cmpReturnVal != int(SCheckResult::ECmpRet::OK))
            stats_.numOfWA++;
    }
    else
    {
        stats_.numOfOK++;
    }
    stats_.numOfTests++;
}


void checkSolution(const SSettings &settings_)
{
    switch(settings_.checkType)
    {
    case ECheckType::DIFF:
        checkDiff(settings_);
        break;
    case ECheckType::GENERATE:
        checkGenerate(settings_);
        break;
    default:
        throw "checkSolution: Sorry but that option isn't available";
        break;
    }
    return;
}

void displayCheckInfoBegin(const SSettings &settings_, const std::string &fullpath_)
{
    std::cout << settings_.checkingStartMessage << std::endl;
    std::cout << std::endl;
    std::cout << settings_.string_Main_pathd << fullpath_ << std::endl;
    std::cout << settings_.string_Solutiond << settings_.solutionSubFolder + settings_.solutionName << std::endl;
    std::cout << settings_.string_Patternd << settings_.pattern << std::endl;
    std::cout << settings_.string_Test_folderd << settings_.testSubFolder << std::endl;
    std::cout << std::endl;
}

void displayCheckSummary(const SSettings &settings_, const SCheckStatistics &checkStats_)
{
    std::cout << "----Summary----" << std::endl;

    if (checkStats_.numOfWA != 0 || checkStats_.numOfErrors != 0 || checkStats_.numOfTLE != 0)
    {
        std::cout << settings_.color_attention << "!!!!!!!!!!!!!" << settings_.color_reset << std::endl;

        std::cout << settings_.color_attention << "!!!WARNING!!!" << settings_.color_reset << " you have at least one " << settings_.waMessage << ", "
        << settings_.errorMessage << " or " << settings_.tleMessage << std::endl;

        std::cout << settings_.color_attention << "!!!!!!!!!!!!!" << settings_.color_reset << std::endl;
    }

    std::cout << "Tests:" << checkStats_.numOfTests << " "
    << settings_.okMessage << ":" << checkStats_.numOfOK  << " "
    << settings_.waMessage << ":" << checkStats_.numOfWA << " "
    << settings_.errorMessage << ":" << checkStats_.numOfErrors << " "
    << settings_.tleMessage << ":" << checkStats_.numOfTLE << " "
    << "seed:" << settings_.generatorSeed <<
     std::endl;
    std::cout << "---------------" << std::endl;
    std::cout.flush();
}

void checkGenerate(const SSettings &settings_)
{
    CStoper stoper;
    std::string fullPath = createFullPath(settings_);
    displayCheckInfoBegin(settings_, fullPath);

    createDir(fullPath + settings_.testSubFolder);

    std::string inputFile;
    std::string outputFile;

    int generatorReturnValue = settings_.generatorSeed;
    SCheckResult checkResult;
    SCheckStatistics checkStats;
    for (int i = 1; i <= settings_.generatorNumOfCalls; i++)
    {
        inputFile = (settings_.testName.size() == 0 ? std::to_string(i) + std::string(".in"): settings_.testName);
        system((settings_.generatorRunPrefix + std::string("\"") + fullPath + settings_.generatorName + std::string("\"") + std::string(" ") + std::to_string(generatorReturnValue)
        + std::string(" ") + settings_.generatorOptions + std::string(" > ") + std::string("\"") + fullPath + settings_.testSubFolder + inputFile + std::string("\"")).c_str());

        generatorReturnValue++;

        if (settings_.pattern.size() != 0)
        {
            outputFile = makeOutFromIn(inputFile);
            system((settings_.patternRunPrefix + std::string("\"") + fullPath + settings_.pattern + std::string("\" < \"") + fullPath + settings_.testSubFolder +  inputFile + std::string("\" > \"")
            + fullPath + settings_.testSubFolder +  outputFile + std::string("\"")).c_str());

            checkResult = checkTest(settings_, stoper, fullPath, inputFile, outputFile, std::string("\033[0m"), i);

            updateCheckStats(checkStats, checkResult);

            if (shouldCheckingBeTerminated(settings_, checkResult) == true)
                break;
            /*if (checkResult.cmpReturnVal != int(checkResult.ECmpRet::OK) && settings_.waStop == true)
				break;
            if (checkResult.solutionReturnVal != int(checkResult.ESolRet::OK) && settings_.noClearStop == true)
                break;*/

        }

    }
    if (settings_.pattern.size() != 0)
    {
        displayCheckSummary(settings_, checkStats);
        /*std::cout << "----Summary----" << std::endl;
        std::cout << "Tests:" << checkStats.numOfTests << " "
        << settings_.okMessage << ":" << checkStats.numOfOK  << " "
        << settings_.waMessage << ":" << checkStats.numOfWA << " "
        << settings_.errorMessage << ":" << checkStats.numOfErrors << " "
        << settings_.tleMessage << ":" << checkStats.numOfTLE << " "
        << "seed:" << settings_.generatorSeed <<
         std::endl;
        std::cout << "---------------" << std::endl;
        std::cout.flush();*/
    }
}


void checkDiff(const SSettings &settings_)
{
    CStoper stoper;
    std::string fullPath = createFullPath(settings_);

    displayCheckInfoBegin(settings_, fullPath);

    CFile dirBrowser;
    dirBrowser.openDir(fullPath + settings_.testSubFolder);

    SDefaultTestSpec fileNameBuf;
    fileNameBuf.in = dirBrowser.nextFile();

    std::vector <std::string> inputNames;
    if (settings_.testName.size() > 0)
        inputNames.push_back(settings_.testName);
    else
    {
        while (fileNameBuf.in.size() > 0)
        {
            inputNames.push_back(fileNameBuf.in);
            fileNameBuf.in = dirBrowser.nextFile();
        }
    }
    dirBrowser.closeDir();
    if (settings_.checkOrder == ECheckOrder::ALPHABETICAL)
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

            checkResult = checkTest(settings_, stoper, fullPath, fileNameBuf.in, fileNameBuf.out, std::string("\033[0m"));

            updateCheckStats(checkStats, checkResult);

            if (shouldCheckingBeTerminated(settings_, checkResult) == true)
                break;
        }
        else if (isSuffix(fileNameBuf.in, std::string(".test")) == true)
        {
            fileNameBuf = convertFormTestToDefault(fullPath + settings_.testSubFolder, fileNameBuf.in);

            checkResult = checkTest(settings_, stoper, fullPath, fileNameBuf.in, fileNameBuf.out, std::string("\033[1;36m"));

            updateCheckStats(checkStats, checkResult);

            if (shouldCheckingBeTerminated(settings_, checkResult) == true)
                break;
        }
    }
    displayCheckSummary(settings_, checkStats);
    /*std::cout << "----Summary----" << std::endl;
    std::cout << "Tests:" << checkStats.numOfTests << " "
    << settings_.okMessage << ":" << checkStats.numOfOK  << " "
    << settings_.waMessage << ":" << checkStats.numOfWA << " "
    << settings_.errorMessage << ":" << checkStats.numOfErrors << " "
    << settings_.tleMessage << ":" << checkStats.numOfTLE <<
     std::endl;
    std::cout << "---------------" << std::endl;
    std::cout.flush();*/

}
SCheckResult checkTest(const SSettings &settings_, CStoper &stoper_, const std::string &fullpath_, const std::string &inputFile_, const std::string &outputFile_, const std::string &testNameColor_, const int testNumber_)
{
	SCheckResult result;
	stoper_.begin();
	result.solutionReturnVal = system(((settings_.limits.memoryLimitArguments.size() != 0 ? settings_.limits.memoryLimitFunctionName + std::string (" ") + settings_.limits.memoryLimitArguments + std::string("\n") : std::string(""))
	 + (settings_.limits.timeLimitArguments.size() != 0 ?  settings_.limits.timeLimitFunctionName + std::string (" ") + settings_.limits.timeLimitArguments + std::string (" ") : std::string (""))
	 + settings_.solutionRunPrefix + std::string("\"") + fullpath_ + settings_.solutionSubFolder + settings_.solutionName + std::string("\" < \"") + fullpath_ + settings_.testSubFolder +  inputFile_ + std::string("\" > tmp/tested.out")
   ).c_str());
	stoper_.end();

    if (settings_.checkType == ECheckType::GENERATE && settings_.testName.size() > 0)
    {
        std::cout << "#";
        std::cout.width(2);
        std::cout << std::left << testNumber_ << " ";
    }

    if (settings_.isColorOutputEnabled == true)
        std::cout << testNameColor_;
	std::cout << inputFile_ << ": ";
	if (settings_.isColorOutputEnabled == true)
        std::cout << "\033[0m";
	std::cout << stoper_.getTimeString() << " ";
	std::cout << "r: " << result.solutionReturnVal << " ";

	result.cmpReturnVal = system((std::string("\"") + settings_.cmpFunction + std::string("\" ") + settings_.cmpOptions + std::string(" \"") + fullpath_ + settings_.testSubFolder +  outputFile_ + std::string("\"  tmp/tested.out")).c_str());
	if (result.cmpReturnVal != int(SCheckResult::ECmpRet::OK) && settings_.waSave == true)
	{
        std::string copiedTestPrefix;
        if (settings_.checkType == ECheckType::GENERATE && settings_.testName.size() > 0)
            copiedTestPrefix = std::to_string(testNumber_) + std::string("::");
        else
            copiedTestPrefix = "";

        copyFile("tmp/tested.out", fullpath_ + settings_.testSubFolder + std::string("solution.wa/"), copiedTestPrefix + outputFile_ + std::string(".wa"));
        copyFile(fullpath_ + settings_.testSubFolder +  inputFile_, fullpath_ + settings_.testSubFolder + std::string("solution.wa/"), copiedTestPrefix + inputFile_);
        copyFile(fullpath_ + settings_.testSubFolder +  outputFile_, fullpath_ + settings_.testSubFolder + std::string("solution.wa/"), copiedTestPrefix + outputFile_);
	}
	if (result.solutionReturnVal != int(SCheckResult::ESolRet::OK))
	{
        if (result.solutionReturnVal == int(SCheckResult::ESolRet::TLE))
            std::cout << settings_.tleMessage + std::string(" ");
        else
            std::cout << settings_.errorMessage + std::string(" ");

        std::cout << std::endl;
	}
	else
    {
        std::cout << (result.cmpReturnVal == int(SCheckResult::ECmpRet::OK) ? settings_.okMessage : settings_.waMessage) << std::endl;
    }
    std::cout.flush();
	return result;
}
