#include "Settings.hpp"
#include "File.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

void loadSettingsFromFile(std::vector<std::string> &args_, std::string settFile_)
{
    std::ifstream in(settFile_);
    if (!in.is_open())
    {
        throw (std::string("SSettings:loadSettingsFromFile: can't open settings file \"") + settFile_ + std::string("\""));
    }
    else
    {
        std::string bufRead;
        do
        {
            bufRead = readLine(in);
            if (bufRead.size() == 0)
                continue;
            args_.push_back(bufRead);
        } while (in.eof() == false);

    }
}

void SSettings::update(std::vector<std::string> &args_)
{
    for (unsigned int i = 0; i < args_.size(); i++)
    {
        if (args_[i][0] != '-')
        {
            this->taskName = args_[i];
            this->solutionName = args_[i];
        }
        else if (args_[i] == "-tera")
            this->terminateAsk = true;
        else if (args_[i] == "-was")
            this->waStop = true;
        else if (args_[i] == "-tles")
            this->tleStop = true;
        else if (args_[i] == "-errs")
            this->errStop = true;
        else if (args_[i] == "-ncs")
        {
            this->noClearStop = true;
            this->waStop = true;
        }
        else if (args_[i] == "-nocolor")
        {
            this->isColorOutputEnabled = false;
            this->okMessage = "OK";
            this->waMessage = "WA";
            this->errorMessage = "ERR";
            this->tleMessage = "TLE";

            this->color_attention = "";
            this->color_reset = "";
            this->color_ok_green = "";
            this->color_wa_red = "";

            this->string_Main_pathd = "Main path:";
            this->string_Solutiond = "Solution:";
            this->string_Patternd = "Pattern:";
            this->string_Test_folderd = "Test subfolder:";

            this->terminationAskMessage = std::string(" #  ") + waMessage + std::string("/") + errorMessage + std::string("/") + tleMessage + std::string(" existed.") + std::string("  #  ") + std::string("Do you want to stop checking?(y or n):");
        }
        else if (args_[i] ==  "-cmpf")
        {
            if (i + 1 < args_.size())
                this->cmpFunction = args_[i + 1];
            else
                throw "SSettings::update: No compare function name provided in next string";
            i += 1;
        }
        else if (args_[i] ==  "-cmpa")
        {
            if (i + 1 < args_.size())
                this->cmpOptions = args_[i + 1];
            else
                throw "SSettings::update: No compare function arguments provided in next string";
            i += 1;
        }
        else if (args_[i] ==  "-oa")
        {
            this->checkOrder = ECheckOrder::ALPHABETICAL;
        }
        else if (args_[i] ==  "-srpref")
        {

            if (i + 1 < args_.size())
                this->solutionRunPrefix = args_[i + 1];
            else
                throw "SSettings::update: No run prefix provided in next string";
            i += 1;
        }
        else if (args_[i] ==  "-grpref")
        {

            if (i + 1 < args_.size())
                this->generatorRunPrefix = args_[i + 1];
            else
                throw "SSettings::update: No run prefix provided in next string";
            i += 1;
        }
        else if (args_[i] ==  "-gena")
        {

            if (i + 1 < args_.size())
                this->generatorOptions = args_[i + 1];
            else
                throw "SSettings::update: No generator arguments provided in next string";
            i += 1;
        }
        else if (args_[i] == "-gseed")
        {
            if (i + 1 < args_.size())
                this->generatorSeed = std::stoi(args_[i + 1]);
            else
                throw "SSettings::update: No generator seed provided in next string";
            i += 1;
        }
        else if (args_[i] == "-gseedt")
        {
            srand(time(0));
            this->generatorSeed = rand();
        }
        else if (args_[i] ==  "-prpref")
        {

            if (i + 1 < args_.size())
                this->patternRunPrefix = args_[i + 1];
            else
                throw "SSettings::update: No run prefix provided in next string";
            i += 1;
        }
        else if (args_[i] ==  "-tf")
        {
            if (i + 1 < args_.size())
                this->testSubFolder = args_[i + 1];
            else
                throw "SSettings::update: No folder name provided in next string";
            i += 1;
        }
        else if (args_[i] == "-sf")
        {
            if (i + 1 < args_.size())
                this->solutionSubFolder = args_[i + 1];
            else
                throw "SSettings::update: No folder name provided in next string";
            i += 1;
        }
        else if (args_[i] == "-sn")
        {
            if (i + 1 < args_.size())
                this->solutionName = args_[i + 1];
            else
                throw "SSettings::update: No solution name provided in next string";
            i += 1;
        }
        else if (args_[i] == "-meml")
        {
	    throw "Unsupported operation";	//!!!!!!!!!!!
            if (i + 1 < args_.size())
                this->limits.virtualMemory = args_[i + 1];
            else
                throw "SSettings::update: No virtual mememory limit provided in next string";
            i += 1;
        }
        else if (args_[i] == "-stal")
        {
            if (i + 1 < args_.size())
                this->limits.stackMemory = args_[i + 1];
            else
                throw "SSettings::update: No stack memory limit provided in next string";
            i += 1;
        }
		else if (args_[i] == "-savwa")
		{
			this->waSave = true;
		}
        else if (args_[i] == "-time")
        {
            if (i + 1 < args_.size())
                this->limits.time = args_[i + 1];
            else
                throw "SSettings::update: No time limit provided in next string";
            i += 1;
        }
        else if (args_[i] == "-tn")
        {
            if (i + 1 < args_.size())
                this->testName = args_[i + 1];
            else
                throw "SSettings::update: No test name provided in next string";
            i += 1;
        }
        else if (args_[i] == "-gen")
        {
            if (i + 1 < args_.size())
                this->generatorName = args_[i + 1];
            else
                throw "SSettings::update: No generator name provided in next string";
            if (i + 2 < args_.size())
                this->generatorNumOfCalls = std::stoi(args_[i + 2]);
            else
                throw "SSettings::update: No generator number of calls provided in next string";
            i += 2;
            this->checkType = ECheckType::GENERATE;
        }
        else if (args_[i] == "-pat")
        {
            if (i + 1 < args_.size())
                this->pattern = args_[i + 1];
            else
                throw "SSettings::update: No pattern program name provided in next string";
            i += 1;
        }
        else if (args_[i] == "-tsf")
        {
            if (i + 1 < args_.size())
            {
                this->taskSuperFolder = args_[i + 1];
            }
            else
                throw "SSettings::update: No task folder provided in next string";
            i += 1;
        }
        else if (args_[i] == "-cmd")
        {
            if (i + 1 < args_.size())
            {
                if (this->taskName.size() > 0)
                    loadSettingsFromFile(args_, createFullPath(*this) + args_[i + 1]);
                else
                    loadSettingsFromFile(args_, args_[i + 1]);
            }
            else
                throw "SSettings::update: No command file provided in next string";
            i += 1;
        }
        else
        {
            throw (std::string("SSettings::update: No arg called \"") + args_[i] + std::string("\" exists"));
            continue;
        }

    }
    if (this->taskName.size() == 0)
        throw "SSettings: No solution name provided";
    this->limits.refresh();
}

std::string createFullPath(const SSettings &settings_)
{
    std::string result = settings_.taskSuperFolder;
    result += settings_.taskName;
    result += "/";
    //result += settings_.testSubFolder;
    return result;
}
