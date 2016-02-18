#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

string text;

int main()
{
	cin >> text;
	//usleep(720000);
	for (int i = text.size() - 1; i >= 0; i--)
	{
		cout << text[i];
	}
	cout << endl;
	srand(time(0));
	return 0;
}
