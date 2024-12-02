#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
	ifstream infile("input.txt");

	string buffer;
	int safe_reports = 0;

	while(getline(infile, buffer)) {
		stringstream ss(buffer);
		int start;
		int next;
		int diff;
		bool ascending = false;
		bool safe = true;

		ss >> start;
		ss >> next;
		diff = abs(start - next);
		if (diff < 1 || diff > 3) {
			//std::cout << "Unsafe in first comparison" << std::endl;
			continue;
		}

		if (next > start) {
			ascending = true;
		}

		start = next;

		while(!ss.eof()) {
			ss >> next;
			diff = abs(start - next);
			if ((diff < 1 || diff > 3) || (ascending && next < start) || (!ascending && next > start)) {
				//std::cout << "Unsafe when comparing " << start << " and " << next << std::endl;
				safe = false;
				break;
			}

			start = next;
		}

		if (safe) {
			safe_reports++;
		}

	}

	cout << "Count of safe reports " << safe_reports << endl;
	return 0;
}
