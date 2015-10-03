#ifndef CSTANKONRAD_SOLUTIONCHECKER_CHECKER_HPP_INCLUDED
#define CSTANKONRAD_SOLUTIONCHECKER_CHECKER_HPP_INCLUDED

#include "Settings.hpp"
#include "Time.hpp"


struct SCheckResult
{
	SCheckResult() {}
	SCheckResult(int _solutionReturnVal, int _cmpReturnVal)
	{
		solutionReturnVal = _solutionReturnVal;
		cmpReturnVal = _cmpReturnVal;
	}
	enum class ESolRet {OK=0, TLE=31744};
    enum class ECmpRet {OK=0};
	int solutionReturnVal;
	int cmpReturnVal;
};

struct SCheckStatistics
{
    unsigned int numOfTests = 0;

    unsigned int numOfOK = 0;
    unsigned int numOfWA = 0;
    unsigned int numOfErrors = 0;
    unsigned int numOfTLE = 0;
};

std::string makeOutFromIn(const std::string &_inFileName);

bool solSortAlphabetical(const std::string &_a, const std::string &_b);

void checkSolution(const SSettings &_settings);

void checkDiff(const SSettings &_settings);
void checkGenerate(const SSettings &_settings);

SCheckResult checkTest(const SSettings &_settings, CStoper &_stoper, const std::string &_fullPath, const std::string &_inputFile, const std::string &_outputFile, const std::string &_testNameColor);

#endif // CSTANKONRAD_SOLUTIONCHECKER_CHECKER_HPP_INCLUDED
