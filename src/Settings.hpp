#ifndef CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED
#define CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED

#include <string>
#include <vector>
#include "Limit.hpp"
/*use existing files; check out using "checker" program;
generate one file with "generator" check out with "pattern" program stop when difference, like before but safe when out is good too*/
enum class ECheckType {DIFF, CHECKER, GENERATE, GENERATE_AND_SAVE};
enum class ECheckOrder {DEFAULT, ALPHABETICAL};
struct SSettings
{
    ECheckType checkType = ECheckType::DIFF;
    ECheckOrder checkOrder = ECheckOrder::DEFAULT;

    bool waStop = false;  //stop when cmp returns <> 0
    //bool outputToLog = false;   // if true then redirect output to tmp/checkLog.txt

    std::string runPrefix = "./";

    std::string subFolder = "";

    std::string taskName;
    std::string cmpFunction = "cmp/default";
    std::string cmpOptions = "";


    std::string okMessage = "\033[1;32mOK\033[0m";
    std::string waMessage = "\033[1;31mWA\033[0m";

    CLimit limits;

    void update(const std::vector<std::string> &_args);
};


#endif // CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED
