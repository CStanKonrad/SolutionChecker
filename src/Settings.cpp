#include "Settings.hpp"
#include <cstring>

void SSettings::update(const std::vector<std::string> &_args)
{
    for (unsigned int i = 0; i < _args.size(); i++)
    {
        if (_args[i][0] != '-')
            this->taskName = _args[i];
        else if (_args[i] == "-check")
            this->checkType = ECheckType::CHECKER;
        else if (_args[i] == "-was")
            this->waStop = true;
        else if (_args[i] == "-nocolor")
        {
            this->okMessage = "OK";
            this->waMessage = "WA";
            this->errorMessage = "ERR";
        }
        else if (_args[i] ==  "-cmpf")
        {
            if (i + 1 < _args.size())
                this->cmpFunction = _args[i + 1];
            else
                throw "SSettings::update: No compare function name provided in next string";
            i += 1;
        }
        else if (_args[i] ==  "-cmpa")
        {
            if (i + 1 < _args.size())
                this->cmpOptions = _args[i + 1];
            else
                throw "SSettings::update: No compare function arguments provided in next string";
            i += 1;
        }
        else if (_args[i] ==  "-oa")
        {
            this->checkOrder = ECheckOrder::ALPHABETICAL;
        }
        else if (_args[i] ==  "-rpref")
        {

            if (i + 1 < _args.size())
                this->runPrefix = _args[i + 1];
            else
                throw "SSettings::update: No run prefix provided in next string";
            i += 1;
        }
        else if (_args[i] ==  "-tf")
        {
            if (i + 1 < _args.size())
                this->testSubFolder = _args[i + 1];
            else
                throw "SSettings::update: No folder name provided in next string";
            i += 1;
        }
        else if (_args[i] == "-sf")
        {
            if (i + 1 < _args.size())
                this->solutionSubFolder = _args[i + 1];
            else
                throw "SSettings::update: No folder name provided in next string";
            i += 1;
        }
        else if (_args[i] == "-meml")
        {
	    throw "Unsupported operation";	//!!!!!!!!!!!
            if (i + 1 < _args.size())
                this->limits.virtualMemory = _args[i + 1];
            else
                throw "SSettings::update: No virtual mememory limit provided in next string";
            i += 1;
        }
        else if (_args[i] == "-stal")
        {
            if (i + 1 < _args.size())
                this->limits.stackMemory = _args[i + 1];
            else
                throw "SSettings::update: No stack memory limit provided in next string";
            i += 1;
        }
		else if (_args[i] == "-savwa")
		{
			this->waSave = true;
		}
        else if (_args[i] == "-time")
        {
            if (i + 1 < _args.size())
                this->limits.time = _args[i + 1];
            else
                throw "SSettings::update: No time limit provided in next string";
            i += 1;
        }
        else if (_args[i] == "-tn")
        {
            if (i + 1 < _args.size())
                this->testName = _args[i + 1];
            else
                throw "SSettings::update: No test name provided in next string";
            i += 1;
        }
        else
        {
            throw (std::string("SSettings::update: No arg called \"") + _args[i] + std::string("\" exists"));
            continue;
        }

    }
    if (this->taskName.size() == 0)
        throw "SSettings: No solution name provided";
    this->limits.refresh();
}
