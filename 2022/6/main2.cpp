#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
	ifstream infile("input.txt");

	string buffer;

	getline(infile, buffer);

	for (int i = 0; i < buffer.size() - 13; i++) {
		string temp = buffer.substr(i, 14);
		sort(temp.begin(), temp.end());

		auto it = unique(temp.begin(), temp.end());
		temp.resize(distance(temp.begin(), it));
		cout << temp << endl;
		if (temp.size() == 14) {
			cout << "Found datastream start at " << i + 13 + 1 << endl;
			break;
		}
	}

	return 0;
}
