#ifndef CSTANKONRAD_TASKCHECKER_SETTINGS_HPP_INCLUDED
#define CSTANKONRAD_TASKCHECKER_SETTINGS_HPP_INCLUDED

#include <string>
#include <vector>
/*use existing files; check out using "checker" program;
generate one file with "generator" check out with "pattern" program stop when difference, like before but safe when out is good too*/
enum class ECheckType {DIFF, CHECKER, GENERATE, GENERATE_AND_SAVE};
enum class ECheckOrder {DEFAULT, ALPHABETICAL};
struct SSettings
{
    ECheckType checkType = ECheckType::DIFF;
    ECheckOrder checkOrder = ECheckOrder::DEFAULT;

    std::string runPrefix = "./";

    std::string subFolder = "";

    std::string taskName;
    std::string cmpFunction = "cmp/default";
    std::string cmpOptions = "";


    std::string okMessage = "\033[1;32mOK\033[0m";
    std::string waMessage = "\033[1;31mWA\033[0m";

    void update(const std::vector<std::string> &_args);
};


#endif // CSTANKONRAD_TASKCHECKER_SETTINGS_HPP_INCLUDED
