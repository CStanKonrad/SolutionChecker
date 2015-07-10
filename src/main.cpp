#include <iostream>
#include "File.hpp"
#include "Settings.hpp"
#include "Checker.hpp"

#include <unistd.h>
#include <sys/time.h>
using namespace std;

SSettings settings;

timeval start, endd;
using namespace std;


int main(int argc, char *argv[])
{
    try
    {
        settings.update(argc, argv);
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
