#ifndef CSTANKONRAD_TASKCHECKER_SETTINGS_HPP_INCLUDED
#define CSTANKONRAD_TASKCHECKER_SETTINGS_HPP_INCLUDED

#include <string>
/*use existing files; check out using "checker" program;
generate one file with "generator" check out with "pattern" program stop when difference, like before but safe when out is good too*/
enum class ECheckType {DIFF, CHECKER, GENERATE, GENERATE_AND_SAVE};
struct SSettings
{
    ECheckType checkType = ECheckType::DIFF;
    std::string taskName;
    std::string cmpFunction = "cmp/default";
    std::string cmpOptions = "-bug";

    std::string okMessage = "\033[1;32mOK\033[0m";
    std::string waMessage = "\033[1;31mWA\033[0m";

    void update(int argc, char *argv[]);
};


#endif // CSTANKONRAD_TASKCHECKER_SETTINGS_HPP_INCLUDED
