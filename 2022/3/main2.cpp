#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int countPriority(const char item)
{
	if (islower(item)) {
		return item - 96;
	} else if (isupper(item)) {
		return item - 38;
	} else {
		cout << "Error value " << item << endl;
		return -1;
	}
}

int main()
{
	ifstream infile("input.txt");

	string first;
	int priority = 0;

	while(getline(infile, first)) {
		char badge;
		string second;
		string third;
		getline(infile, second);
		getline(infile, third);

		for (auto c : first) {
			if (second.find(c) != string::npos) {
				if (third.find(c) != string::npos){
					badge = c;
					break;
				}
			}
		}

		priority += countPriority(badge);
	}

	cout << "Final priority " << priority << endl;

	return 0;
}
