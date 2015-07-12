#ifndef CSTANKONRAD_SOLUTIONCHECKER_TIME_HPP_INCLUDED
#define CSTANKONRAD_SOLUTIONCHECKER_TIME_HPP_INCLUDED

#include <ctime>
#include <string>
#include <sstream>

#include <unistd.h>
#include <sys/time.h>


class CStoper
{
private:
    timeval startTime;
    timeval endTime;

    unsigned long long elapsedTime = 0LL;

    bool isEnabled = false;
public:
    void begin();
    void end();
    double getTime();
    std::string getTimeString();
};


#endif // CSTANKONRAD_SOLUTIONCHECKER_TIME_HPP_INCLUDED
