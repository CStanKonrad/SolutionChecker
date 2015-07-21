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
	enum class ESolRet {OK=0};
    enum class ECmpRet {OK=0};
	int solutionReturnVal;
	int cmpReturnVal;
};

/* 'Creates' path to task folder */
std::string createFullPath(const std::string &_taskName);

std::string makeOutFromIn(const std::string &_inFileName);

void checkSolution(const SSettings &_settings);

void checkDiff(const SSettings &_settings);

SCheckResult checkTest(const SSettings &_settings, CStoper &_stoper, const std::string &_fullPath, const std::string &_inputFile, const std::string &_outputFile);

#endif // CSTANKONRAD_SOLUTIONCHECKER_CHECKER_HPP_INCLUDED
