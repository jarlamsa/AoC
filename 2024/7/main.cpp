#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool checkEquations(uint64_t result, vector<uint64_t> operands)
{
	// Store the operators in vector, 1 is plus 2 is multiplier
	// i tells the amount of plusses
	for (int i = operands.size() - 1; i >= 0; i--) {
		vector<int> operators;
		// Amount of multipliers
		int j = operands.size() - 1 - i;
		for (int k = 0; k < i; k++) {
			operators.emplace_back(1);
		}
		for (int k = 0; k < j; k++) {
			operators.emplace_back(2);
		}

		do {

			uint64_t start = operands.at(0);
			for (int k = 1; k < operands.size(); k++) {
				uint64_t next = operands.at(k);
				int op = operators.at(k-1);
				if (op == 1) {
					start += next;
				} else {
					start *= next;
				}
				if (start > result) {
					break;
				}
			}
			if (start == result) {
				return true;
			}
		} while (std::next_permutation(operators.begin(), operators.end()));

	}

	return false;
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	uint64_t sum = 0;

	while(getline(infile, buffer)) {
		vector<uint64_t> operands;
		string::size_type colpos = buffer.find(':');
		uint64_t result = stoll(buffer.substr(0, colpos));
		stringstream ss(buffer.substr(colpos+1));

		while(!ss.eof()) {
			uint64_t operand;
			ss >> operand;
			operands.emplace_back(operand);
		}
		if (checkEquations(result, operands)) {
			sum += result;
		}
	}

	cout << "Sum of correct results " << sum << endl;
	return 0;
}
