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


void loadArgs(vector<std::string> &_args, string _settFile, int _argc, char *_argv[])
{
    loadSettingsFromFile(_args, _settFile);
    for (int i = 1; i < _argc; i++)
    {
        _args.push_back(_argv[i]);
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
    catch (const char *_bug)
    {
        cerr << "Error: " << _bug << endl;
    }
    catch (string _bug)
    {
	cerr << "Error: " << _bug << endl;
    }
    //cerr << settings.cmpOptions << endl;
    //cerr << (int)settings.checkType << endl;
    return 0;
}
