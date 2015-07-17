#ifndef CSTANKONRAD_SOLUTIONCHECKER_LIMIT_HPP_INCLUDED
#define CSTANKONRAD_SOLUTIONCHECKER_LIMIT_HPP_INCLUDED

#include <string>

class CLimit
{
private:
    const std::string UNLIMITED = "unlimited";
public:
    std::string memoryLimitFunctionName = "ulimit";
    std::string memoryLimitArguments = "";

    std::string timeLimitFunctionName = "timeout";
    std::string timeLimitArguments = "";

    /*Memory: 0 means unlimited */
    std::string virtualMemory = "";   //in KB
    std::string stackMemory = "";       //in KB

    /* time */
    std::string time = "";

    /* Loads stand alone args into arguments */
    void refresh();

};


#endif
