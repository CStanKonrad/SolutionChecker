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
    bool errStop = false;   //stop when solution returns <> 0
    bool tleStop = false;   //stop when time limit exceeded
    bool noClearStop = false;   //stop when cmp returns <> 0 or solution returns <> 0 or time limit exceeded
    bool waSave = false;	//save ouptut from solution if answer is wront to /.../wa
    bool terminateAsk = false; //true = ask before termination (checking with flags -was -ncs option)
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

    std::string color_attention = "\033[1;41m";
    std::string color_reset = "\033[0m";
    std::string color_ok_green = "\033[1;32m";
    std::string color_wa_red = "\033[1;31m";

    std::string okMessage = "\033[1;32mOK\033[0m";
    std::string waMessage = "\033[1;31mWA\033[0m";
    std::string errorMessage = "\033[1;41mERR\033[0m";
    std::string tleMessage = "\033[1;43mTLE\033[0m";

    std::string checkingStartMessage = "#######################################\n# SolutionChecker - starting checking #\n#######################################";

    std::string string_Main_pathd = "\033[1;37mMain path:\033[0m";
    std::string string_Solutiond = "\033[1;37mSolution:\033[0m";
    std::string string_Patternd = "\033[1;37mPattern:\033[0m";
    std::string string_Test_folderd = "\033[1;37mTest subfolder:\033[0m";

    std::string terminationAskMessage = std::string("\033[1;37m\033[45m # \033[0m ") + waMessage + std::string("/") + errorMessage + std::string("/") + tleMessage + std::string(" \033[1;37mexisted.") + std::string(" \033[45m # \033[0m ") + std::string("\033[1;37mDo you want to stop checking?(y or n):\033[0m");

    CLimit limits;

    void update(std::vector<std::string> &args_);
};


void loadSettingsFromFile(std::vector<std::string> &args_, std::string settFile_);

/* 'Creates' path to task folder */
std::string createFullPath(const SSettings &settings_);


#endif // CSTANKONRAD_SOLUTIONCHECKER_SETTINGS_HPP_INCLUDED
