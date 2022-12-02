#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int countScore(char gnome, char me)
{
	int result = 0;

	switch (me)
	{
	case 'X':
		if (gnome == 'A')
			result = 4;
		else if (gnome == 'B')
			result = 1;
		else if (gnome == 'C')
			result = 7;
		break;
	case 'Y':
		if (gnome == 'A')
			result = 8;
		else if (gnome == 'B')
			result = 5;
		else if (gnome == 'C')
			result = 2;
		break;
	case 'Z':
		if (gnome == 'A')
			result = 3;
		else if (gnome == 'B')
			result = 9;
		else if (gnome == 'C')
			result = 6;
		break;
	default:
		break;
	}
	return result;
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	char gnome;
	char me;
	int score = 0;

	while(getline(infile, buffer)) {
		stringstream ss(buffer);
		ss >> gnome;
		ss >> me;
		score += countScore(gnome, me);
	}

	cout << "Final score: " << score << endl;
	return 0;
}
