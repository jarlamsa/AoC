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

	string buffer;
	int priority = 0;

	while(getline(infile, buffer)) {
		vector<char> duplicates;
		int split = buffer.size() / 2;
		string first = buffer.substr(0, split);
		string second = buffer.substr(split);

		for (auto c : first) {
			if (second.find(c) != string::npos) {
				duplicates.push_back(c);
			}
		}

		sort(duplicates.begin(), duplicates.end());
		auto it = unique(duplicates.begin(), duplicates.end());
		duplicates.resize(distance(duplicates.begin(), it));

		for (auto c : duplicates) {
			priority += countPriority(c);
		}
	}

	cout << "Final priority " << priority << endl;

	return 0;
}
