#include "Settings.hpp"
#include "File.hpp"
#include <cstring>
#include <fstream>

void loadSettingsFromFile(std::vector<std::string> &_args, std::string _settFile)
{
    std::ifstream in(_settFile);
    if (!in.is_open())
    {
        throw (std::string("SSettings:loadSettingsFromFile: can't open settings file \"") + _settFile + std::string("\""));
    }
    else
    {
        std::string bufRead;
        do
        {
            bufRead = readLine(in);
            _args.push_back(bufRead);
        } while (in.eof() == false);

    }
}

void SSettings::update(std::vector<std::string> &_args)
{
    for (unsigned int i = 0; i < _args.size(); i++)
    {
        if (_args[i][0] != '-')
            this->taskName = _args[i];
        else if (_args[i] == "-was")
            this->waStop = true;
        else if (_args[i] == "-nocolor")
        {
            this->isColorOutputEnabled = false;
            this->okMessage = "OK";
            this->waMessage = "WA";
            this->errorMessage = "ERR";
            this->tleMessage = "TLE";
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
        else if (_args[i] ==  "-srpref")
        {

            if (i + 1 < _args.size())
                this->solutionRunPrefix = _args[i + 1];
            else
                throw "SSettings::update: No run prefix provided in next string";
            i += 1;
        }
        else if (_args[i] ==  "-grpref")
        {

            if (i + 1 < _args.size())
                this->generatorRunPrefix = _args[i + 1];
            else
                throw "SSettings::update: No run prefix provided in next string";
            i += 1;
        }
        else if (_args[i] ==  "-gena")
        {

            if (i + 1 < _args.size())
                this->generatorOptions = _args[i + 1];
            else
                throw "SSettings::update: No generator arguments provided in next string";
            i += 1;
        }
        else if (_args[i] ==  "-prpref")
        {

            if (i + 1 < _args.size())
                this->patternRunPrefix = _args[i + 1];
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
        else if (_args[i] == "-gen")
        {
            if (i + 1 < _args.size())
                this->generatorName = _args[i + 1];
            else
                throw "SSettings::update: No generator name provided in next string";
            if (i + 2 < _args.size())
                this->generatorNumOfCalls = std::stoi(_args[i + 2]);
            else
                throw "SSettings::update: No generator number of calls provided in next string";
            i += 2;
            this->checkType = ECheckType::GENERATE;
        }
        else if (_args[i] == "-pat")
        {
            if (i + 1 < _args.size())
                this->pattern = _args[i + 1];
            else
                throw "SSettings::update: No pattern program name provided in next string";
            i += 1;
        }
        else if (_args[i] == "-tsf")
        {
            if (i + 1 < _args.size())
            {
                this->taskSuperFolder = _args[i + 1];
            }
            else
                throw "SSettings::update: No task folder provided in next string";
            i += 1;
        }
        else if (_args[i] == "-cmd")
        {
            if (i + 1 < _args.size())
            {
                if (this->taskName.size() > 0)
                    loadSettingsFromFile(_args, createFullPath(*this) + _args[i + 1]);
                else
                    loadSettingsFromFile(_args, _args[i + 1]);
            }
            else
                throw "SSettings::update: No command file provided in next string";
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

std::string createFullPath(const SSettings &_settings)
{
    std::string result = _settings.taskSuperFolder;
    result += _settings.taskName;
    result += "/";
    //result += _settings.testSubFolder;
    return result;
}
