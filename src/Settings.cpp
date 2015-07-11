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
        else if (_args[i] == "-nocolor")
        {
            this->okMessage = "OK";
            this->waMessage = "WA";
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
        else if (_args[i] ==  "-f")
        {
            if (i + 1 < _args.size())
                this->subFolder = _args[i + 1];
            else
                throw "SSettings::update: No folder name provided in next string";
            i += 1;
        }
        else
        {
            throw (std::string("SSettings::update: No arg called \"") + _args[i] + std::string("\" exists")).c_str();
            continue;
        }

    }
}
