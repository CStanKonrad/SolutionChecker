#include "Settings.hpp"
#include <cstring>

void SSettings::update(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
            this->taskName = std::string(argv[i]);
        else if (strcmp(argv[i], "-check") == 0)
            this->checkType = ECheckType::CHECKER;
        else if (strcmp(argv[i], "-nocolor") == 0)
        {
            this->okMessage = "OK";
            this->waMessage = "WA";
        }
        else if (strcmp(argv[i], "-cmpf") == 0)
        {
            if (i + 1 < argc)
                this->cmpFunction = argv[i + 1];
            else
                throw "SSettings::update: No compare function name provided in next string";
            i += 1;
        }
        else if (strcmp(argv[i], "-cmpa") == 0)
        {
            if (i + 1 < argc)
                this->cmpOptions = argv[i + 1];
            else
                throw "SSettings::update: No compare function arguments provided in next string";
            i += 1;
        }
        else
        {
            throw (std::string("SSettings::update: No arg called \"") + std::string(argv[i]) + std::string("\" exists")).c_str();
            continue;
        }

    }
}
