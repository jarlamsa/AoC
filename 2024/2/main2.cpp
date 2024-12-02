#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool isAscending(string buffer)
{
	int ascends = 0;
	int descends = 0;
	stringstream ss(buffer);

	int start;
	int next;
	ss >> start;
	ss >> next;

	do {
		if (start < next) {
			ascends++;
		} else {
			descends++;
		}
		start = next;
		ss >> next;
	} while(!ss.eof());

	return ascends > descends;
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	int safe_reports = 0;
	int line = 0;

	while(getline(infile, buffer)) {
		line++;
		stringstream ss(buffer);
		int start;
		int next;
		int diff;
		int errors = 0;
		bool ascending = isAscending(buffer);
		bool safe = true;

		ss >> start;
		ss >> next;
		diff = abs(start - next);
		if ((diff < 1 || diff > 3) || (ascending && next < start) || (!ascending && next > start)) {
			if (errors == 0) {
				int third;
				ss >> third;
				diff = abs(start - third);
				errors++;

				if ((diff < 1 || diff > 3) || (ascending && third < start) || (!ascending && third > start)) {
					diff = abs(next - third);
					if ((diff < 1 || diff > 3) || (ascending && third < next) || (!ascending && third > next)) {
						std::cout << "Unsafe in first comparison on line " << line << std::endl;
						continue;
					} else {
						start = next;
						next = third;
					}
				} else {
					next = third;
				}
			} else {
				std::cout << "Unsafe in first comparison on line " << line << std::endl;
				continue;
			}
		}

		start = next;

		while(!ss.eof()) {
			ss >> next;
			diff = abs(start - next);
			if ((diff < 1 || diff > 3) || (ascending && next < start) || (!ascending && next > start)) {
				if (errors == 0) {
					errors++;
					continue;
				}
				std::cout << "Unsafe when comparing " << start << " and " << next << " on line " << line << std::endl;
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
