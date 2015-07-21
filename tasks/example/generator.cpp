#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

int main(int _argc, char *_argv[])
{
	if (_argc < 3)
	{
		cerr << "Generator: No n provded" << endl;
		return -1;
	}
	srand(stoi(_argv[1]));
	int n = stoi(string(_argv[2]));
	for (int i = 0; i < n; i++)
	{
		putchar((rand()%('z' - 'a' + 1)) + 'a');
	}
	return rand();
}
