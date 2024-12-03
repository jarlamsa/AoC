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
	std::cout << "Left: " << left << " Right: " << right << " result: " << result << std::endl;
	return result;

}

int64_t findMul(string mulstring)
{
	int64_t sum = 0;
	string operands;
	string::size_type startpos = mulstring.find("mul(");

	while(startpos != string::npos) {
		string::size_type endpos = mulstring.find(")", startpos + 4);

		if (startpos == string::npos) {
			return 0;
		}
		operands = mulstring.substr(startpos + 4, endpos - (startpos+4 ));
		sum += parseOperation(operands);
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
		sum += findMul(buffer);
	}

	std::cout << "Sum of operations " << sum << std::endl;

	return 0;
}
