#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool doesAreaContain(int aStart, int aEnd, int bStart, int bEnd)
{
	return (aStart <= bStart && aEnd >= bEnd) || (bStart <= aStart && bEnd >= aEnd);
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	int contained = 0;

	while(getline(infile, buffer)) {
		string first = buffer.substr(0, buffer.find(","));
		string second = buffer.substr(buffer.find(",")+1);

		int aStart = stoi(first.substr(0,first.find("-")));
		int aEnd = stoi(first.substr(first.find("-") + 1));

		int bStart = stoi(second.substr(0,second.find("-")));
		int bEnd = stoi(second.substr(second.find("-") + 1));

		contained += doesAreaContain(aStart, aEnd, bStart, bEnd);
	}

	cout << "Areas contained in other: " << contained << endl;

	return 0;
}
