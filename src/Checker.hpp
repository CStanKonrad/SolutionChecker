#ifndef CSTANKONRAD_TASKCHECKER_CHECKER_HPP_INCLUDED
#define CSTANKONRAD_TASKCHECKER_CHECKER_HPP_INCLUDED

#include "Settings.hpp"

#define OK_MESSAGE "\033[1;32mOK\033[0m"
#define WA_MESSAGE "\033[1;31mWA\033[0m"

/* 'Creates' path to task folder */
std::string createFullPath(const std::string &_taskName);

std::string makeOutFromIn(const std::string &_inFileName);

void checkSolution(const SSettings &_settings);

void checkDiff(const SSettings &_settings);

#endif // CSTANKONRAD_TASKCHECKER_CHECKER_HPP_INCLUDED
