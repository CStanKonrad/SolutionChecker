#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

bool writeBug = false;
bool writeFileNames = false;

string waColor = "\033[1;33m";
string clearColor = "\033[0m";

string patStr;
string tesStr;

bool isWhite(char _c)
{
	if (_c == ' ' || _c == '	' || _c == '\n' || _c == '\r')
		return true;
	else
		return false;
}

bool readNext(ifstream &_file, string &_str)
{
	while(isWhite(_file.peek()))
		_file.get();
	if (_file.eof() == false)
	{
		_file >> _str;
		return true;
	}
	else
		return false;
}

int main(int _argc, char *_argv[])
{
	for (int i = 1; i < _argc; i++)
	{
		if (_argv[i][0] != '-')
		{
			if (i + 1 < _argc)
			{
				patStr = string(_argv[i]);
				tesStr = string(_argv[i + 1]);
				break;
			}
			else
			{
				cerr << "CMP: cmp/default: No second output file path" << endl;
				return -2;
			}	
		}
		else
		{
			if (strcmp(_argv[i], "-bug") == 0)
				writeBug = true;
			else if (strcmp(_argv[i], "-fname") == 0)
				writeFileNames = true;
			else if (strcmp(_argv[i], "-nocolor") == 0)
			{
				waColor = "";
				clearColor = "";
			}
			else
			{
				cerr << "CMP: No arg called \"" << _argv[i] << "\" exists" << endl;
			}
		}
	}
	if (writeFileNames)
		cout << patStr << "	" << tesStr << endl;
		
	ifstream pat(patStr.c_str());
	ifstream tes(tesStr.c_str());
	
	if (pat.is_open() == false)
	{
		cerr << "CMP: Can't open:" << patStr << endl;
		return -2;
	}
	if (tes.is_open() == false)
	{
		cerr << "CMP: Can't open: " << tesStr << endl;
		return -2;
	}
	
	int strNr = 1;
	bool pb, tb;
	while (true)
	{
		pb = readNext(pat, patStr);
		tb = readNext(tes, tesStr);

		if (pb == false && tb == false)
			break;
		else if (pb == false || tb == false)
		{
			if (writeBug)
				cout << waColor << (pb == false ? "Output file is too long" : "Output file is too short") << clearColor << endl;
			
			pat.close();
			tes.close();
			return -1;
		}

		if (patStr != tesStr)
		{
			if (writeBug)
			{
				pat.close();
				tes.close();
				cout << waColor << "String:" << clearColor << strNr << waColor << " Expected:" << clearColor << patStr << waColor << " Readed:" << clearColor << tesStr << endl;
			}
			return -1;
		}
		
		strNr++;
	}
	pat.close();
	tes.close();
	return 0;
}
