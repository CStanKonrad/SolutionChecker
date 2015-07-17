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
    ifstream in(_settFile);
    if (!in.is_open())
    {
        throw (string("main:loadArgs: can't open settings file \"") + _settFile + string("\"")).c_str();
    }
    else
    {
        string bufRead;
        do
        {
            bufRead = readLine(in);
            _args.push_back(bufRead);
        } while (in.eof() == false);

    }
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
    //cerr << settings.cmpOptions << endl;
    //cerr << (int)settings.checkType << endl;
    return 0;
}
