#ifndef CSTANKONRAD_SOLUTIONCHECKER_CHECKER_HPP_INCLUDED
#define CSTANKONRAD_SOLUTIONCHECKER_CHECKER_HPP_INCLUDED

#include "Settings.hpp"
#include "Time.hpp"


struct SCheckResult
{
	SCheckResult() {}
	SCheckResult(int solutionReturnVal_, int cmpReturnVal_)
	{
		solutionReturnVal = solutionReturnVal_;
		cmpReturnVal = cmpReturnVal_;
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

std::string makeOutFromIn(const std::string &inFileName_);

bool solSortAlphabetical(const std::string &a_, const std::string &b_);

bool shouldCheckingBeTerminated(const SSettings &settings_, const SCheckResult &checkResult_);

void checkSolution(const SSettings &settings_);

void checkDiff(const SSettings &settings_);
void checkGenerate(const SSettings &settings_);



SCheckResult checkTest(const SSettings &settings_, CStoper &stoper_, const std::string &fullPath_, const std::string &inputFile_, const std::string &outputFile_, const std::string &testNameColor_, const int testNumber_ = -1);

#endif // CSTANKONRAD_SOLUTIONCHECKER_CHECKER_HPP_INCLUDED
