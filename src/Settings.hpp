#ifndef CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED
#define CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED

#include <string>
#include <vector>
#include "Limit.hpp"
/*use existing files; check out using "checker" program;
generate one file with "generator" check out with "pattern" program stop when difference, like before but safe when out is good too*/
enum class ECheckType {DIFF, GENERATE};
enum class ECheckOrder {DEFAULT, ALPHABETICAL};
struct SSettings
{
    ECheckType checkType = ECheckType::DIFF;
    ECheckOrder checkOrder = ECheckOrder::DEFAULT;

    bool waStop = false;	//stop when cmp returns <> 0
    bool noClearStop = false;   //stop when cmp returns <> 0 or solution returns <> 0 or time limit exceeded
    bool waSave = false;	//save ouptut from solution if answer is wront to /.../wa
    bool isColorOutputEnabled = true;
    //bool outputToLog = false;   // if true then redirect output to tmp/checkLog.txt

    std::string solutionRunPrefix = ""; //for example = "python2 "

    std::string testSubFolder = "";
    std::string solutionName;   //solution file name
    std::string solutionSubFolder = "";

    std::string testName = "";  //if testName.size() > 0 then only this test is checked
    std::string taskSuperFolder = "tasks/";
    std::string taskName;


    std::string generatorName = "";
    std::string generatorOptions = "";
    std::string generatorRunPrefix = "";
    int generatorSeed = 0;
    int generatorNumOfCalls = 0;
    std::string pattern = "";   //pattern program for genarate checking
    std::string patternRunPrefix = "";
    std::string cmpFunction = "cmp/default";
    std::string cmpOptions = "";


    std::string okMessage = "\033[1;32mOK\033[0m";
    std::string waMessage = "\033[1;31mWA\033[0m";
    std::string errorMessage = "\033[1;41mERR\033[0m";
    std::string tleMessage = "\033[1;43mTLE\033[0m";

    CLimit limits;

    void update(std::vector<std::string> &_args);
};


void loadSettingsFromFile(std::vector<std::string> &_args, std::string _settFile);

/* 'Creates' path to task folder */
std::string createFullPath(const SSettings &_settings);


#endif // CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED
