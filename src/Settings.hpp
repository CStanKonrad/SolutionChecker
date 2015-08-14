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
    bool waSave = false;	//save ouptut from solution if answer is wront to /.../wa
    //bool outputToLog = false;   // if true then redirect output to tmp/checkLog.txt

    std::string solutionRunPrefix = ""; //for example = "python2 "

    std::string testSubFolder = "";
    std::string solutionSubFolder = "";

    std::string testName = "";  //if testName.size() > 0 then only this test is checked
    std::string taskName;

    std::string generatorName = "";
    std::string generatorOptions = "";
    std::string generatorRunPrefix = "";
    std::string pattern = "";   //pattern program for genarate checking
    std::string patternRunPrefix = "";
    int generatorNumOfCalls = 0;
    std::string cmpFunction = "cmp/default";
    std::string cmpOptions = "";


    std::string okMessage = "\033[1;32mOK\033[0m";
    std::string waMessage = "\033[1;31mWA\033[0m";
    std::string errorMessage = "\033[1;41mERR\033[0m";

    CLimit limits;

    void update(const std::vector<std::string> &_args);
};


#endif // CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED
