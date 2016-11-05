#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

bool writeBug = false;
bool writeFileNames = false;

string waColor = "\033[1;33m";
string strongWhiteColor = "\033[1;37m";
string clearColor = "\033[0m";

string patStr;
string tesStr;

bool isWhite(char c_)
{
	if (c_ == ' ' || c_ == '	' || c_ == '\n' || c_ == '\r')
		return true;
	else
		return false;
}

bool readNext(ifstream &file_, string &str_, int &lineNr_)
{
	while(isWhite(file_.peek()))
	{
		if (file_.get() == '\n')
			++lineNr_;

	}
	if (file_.eof() == false)
	{
		file_ >> str_;
		return true;
	}
	else
		return false;
}

string cutString(string str_, unsigned int maxSize_ = 20)	//cuts string when bigger than maxSize_
{
	string result = "";
	for (unsigned int i = 0; i < min<unsigned int>(maxSize_, str_.size()); i++)
	{
		result += str_[i];
	}
	if (maxSize_ < str_.size())
		result += "...";
	return result;
}

int main(int argc_, char *argv_[])
{
	for (int i = 1; i < argc_; i++)
	{
		if (argv_[i][0] != '-')
		{
			if (i + 1 < argc_)
			{
				patStr = string(argv_[i]);
				tesStr = string(argv_[i + 1]);
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
			if (strcmp(argv_[i], "-bug") == 0)
				writeBug = true;
			else if (strcmp(argv_[i], "-fname") == 0)
				writeFileNames = true;
			else if (strcmp(argv_[i], "-nocolor") == 0)
			{
				waColor = "";
				clearColor = "";
			}
			else
			{
				cerr << "CMP: No arg called \"" << argv_[i] << "\" exists" << endl;
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
	int patLineNr = 1;
	int tesLineNr = 1;
	bool pb, tb;
	while (true)
	{
		pb = readNext(pat, patStr, patLineNr);
		tb = readNext(tes, tesStr, tesLineNr);

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
				cout << waColor << "lnp/t:" << clearColor << strongWhiteColor << patLineNr << clearColor << "/" << strongWhiteColor << tesLineNr << clearColor
				<< waColor << " str:" << clearColor << strNr << waColor << " exp:" << clearColor << cutString(patStr) << waColor << " read:" << clearColor << cutString(tesStr) << endl;
			}
			return -1;
		}

		strNr++;
	}
	pat.close();
	tes.close();
	return 0;
}
