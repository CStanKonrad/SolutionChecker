#include <iostream>
#include <vector>

#include <fstream>

#include "File.hpp"
#include "Settings.hpp"
#include "Checker.hpp"

#include <unistd.h>
#include <sys/time.h>
using namespace std;

SSettings settings;

timeval start, endd;
using namespace std;


void loadArgs(vector<std::string> &args_, string settFile_, int argc_, char *argv_[])
{
    loadSettingsFromFile(args_, settFile_);
    for (int i = 1; i < argc_; i++)
    {
        args_.push_back(argv_[i]);
    }
}


vector<std::string> arguments;
int main(int argc, char *argv[])
{

    try
    {
        loadArgs(arguments, "settings.txt", argc, argv);
        settings.update(arguments);
        checkSolution(settings);
    }
    catch (const char *bug_)
    {
        cerr << "Error: " << bug_ << endl;
    }
    catch (string bug_)
    {
	cerr << "Error: " << bug_ << endl;
    }
    //cerr << settings.cmpOptions << endl;
    //cerr << (int)settings.checkType << endl;
    return 0;
}
