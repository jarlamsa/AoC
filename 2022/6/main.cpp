#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
	ifstream infile("input.txt");

	string buffer;

	getline(infile, buffer);

	for (int i = 0; i < buffer.size() - 3; i++) {
		string temp = buffer.substr(i, 4);
		sort(temp.begin(), temp.end());

		auto it = unique(temp.begin(), temp.end());
		temp.resize(distance(temp.begin(), it));
		cout << temp << endl;
		if (temp.size() == 4) {
			cout << "Found datastream start at " << i + 3 + 1 << endl;
			break;
		}
	}

	return 0;
}
