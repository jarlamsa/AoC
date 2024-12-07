#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

uint64_t concatenate(uint64_t i, uint64_t j)
{
	uint64_t length = log10l(j) + 1;
	//std::cout << "Length of j is " << length << " digits " << std::endl; 
	//return stoll(std::to_string(i)+std::to_string(j));
	uint64_t result = i*(pow(10,length))+j;
	//std::cout << "Concatenated " << i << " and " << j << " to " << result <<std::endl;
	return result;
}

bool checkEquations(uint64_t result, vector<uint64_t> operands)
{
	if (operands.at(0) > result) {
		return false;
	}

	if (operands.size() == 1) {
		if (operands.at(0) == result) {
			return true;
		} else {
			return false;
		}
	}

	std::vector<uint64_t> plussed;
	std::vector<uint64_t> multiplied;
	std::vector<uint64_t> concatenated;

	plussed.emplace_back(operands.at(0) + operands.at(1));
	multiplied.emplace_back(operands.at(0) * operands.at(1));
	concatenated.emplace_back(concatenate(operands.at(0), operands.at(1)));

	for (int i = 2; i < operands.size(); i++) {
		plussed.emplace_back(operands.at(i));
		multiplied.emplace_back(operands.at(i));
		concatenated.emplace_back(operands.at(i));
	}

	if (checkEquations(result, plussed)) return true;
	if (checkEquations(result, multiplied)) return true;
	if (checkEquations(result, concatenated)) return true;

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
