#ifndef CSTANKONRAD_TESTCONVERTER_HPP_INCLUDED
#define CSTANKONRAD_TESTCONVERTER_HPP_INCLUDED

#include <string>
#include "File.hpp"

struct SDefaultTestSpec
{
    std::string in = "";
    std::string out = "";
};

SDefaultTestSpec convertFormTestToDefault(const std::string &path_, const std::string &testFileName_); //open (_path + _testFileName)

#endif // CSTANKONRAD_TESTCONVERTER_HPP_INCLUDED
