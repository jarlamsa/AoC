#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int64_t parseOperation(string op)
{
	stringstream ss(op);
	string left;
	string right;
	string::size_type pos;

	getline(ss, left, ',' );
	getline(ss, right);

	if (left.length() == 0 || right.length() == 0) {
		return 0;
	}

	pos = left.find_first_not_of("0123456789");
	if (pos != string::npos) {
		return 0;
	}
	pos = right.find_first_not_of("0123456789");
	if (pos != string::npos) {
		return 0;
	}

	
	int64_t result = (stoi(left) * stoi(right));
	return result;

}

int64_t findMul(string mulstring)
{
	int64_t sum = 0;
	string operands;
	string::size_type startpos = mulstring.find("mul(");

	std::vector<std::pair<string::size_type, string::size_type>> intervals;

	string::size_type intervalstart = 0;
	string::size_type intervalend = mulstring.find("don't()");
	while(intervalstart != string::npos) {
		std::pair<string::size_type, string::size_type> interval;
		interval = make_pair(intervalstart, intervalend);
		intervals.emplace_back(interval);
		intervalstart = mulstring.find("do()", intervalend);
		intervalend = mulstring.find("don't()", intervalstart);
	}

	for (auto i : intervals) {
		std::cout << "Start " << i.first << " end " << i.second << endl;
	}

	while(startpos != string::npos) {
		bool enabled = false;
		string::size_type endpos = mulstring.find(")", startpos + 4);

		if (startpos == string::npos) {
			return 0;
		}
		for (auto i : intervals) {
			//std::cout << "Startpos " << startpos << std::endl;
			if (i.first < startpos && startpos < i.second) {
				enabled = true;
			}
		}
		operands = mulstring.substr(startpos + 4, endpos - (startpos+4 ));

		if (enabled) {
			sum += parseOperation(operands);
		}

		startpos = mulstring.find("mul(", startpos + 4);
	}

	return sum;
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	int64_t sum = 0;

	while(getline(infile, buffer)) {
		std::cout << "New line" << std::endl;
		sum += findMul(buffer);
	}

	std::cout << "Sum of operations " << sum << std::endl;

	return 0;
}
