#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <bitset>
#include <queue>

using namespace std;

void compute(vector<uint64_t> &operations, uint64_t &A, uint64_t &B, uint64_t &C, uint64_t &IP, vector<uint64_t> &output)
{
	uint64_t inst = operations.at(IP);
	uint64_t operand = operations.at(IP+1);
	IP += 2;

	switch (inst)
	{
	//adv
	case 0:
		{
			uint64_t numerator = A;
			uint64_t denominator = 1;
			if (operand < 4) {
				denominator = pow(2, operand);
			} else if (operand == 4) {
				denominator = pow(2, A);
			} else if (operand == 5) {
				denominator = pow(2, B);
			} else if (operand == 6) {
				denominator = pow(2, C);
			} else {
				std::cout << "Reserved, program not valid" << std::endl;
				IP = operations.size();
				break;
			}
			A = numerator / denominator;
			break;
		}
	//bxl
	case 1:
		{
			B = B ^ operand;
			break;
		}
	//bst
	case 2:
		{
			uint64_t result = 0;
			if (operand < 4) {
				result = operand % 8;
			} else if (operand == 4) {
				result = A % 8;
			} else if (operand == 5) {
				result = B % 8;
			} else if (operand == 6) {
				result = C % 8;
			} else {
				std::cout << "Reserved, program not valid" << std::endl;
				IP = operations.size();
				break;
			}
			B = result;
			break;
		}
	//jnz
	case 3:
		{
			if (A != 0) {
				IP = operand;
			}
			break;
		}
	//bxc
	case 4:
		{
			B = B ^ C;
			break;
		}
	//out
	case 5:
		{
			uint64_t result = 0;
			if (operand < 4) {
				result = operand % 8;
			} else if (operand == 4) {
				result = A % 8;
			} else if (operand == 5) {
				result = B % 8;
			} else if (operand == 6) {
				result = C % 8;
			} else {
				std::cout << "Reserved, program not valid" << std::endl;
				IP = operations.size();
				break;
			}
			output.emplace_back(result);
			break;
		}
	//bdv
	case 6:
		{
			uint64_t numerator = A;
			uint64_t denominator = 1;
			if (operand < 4) {
				denominator = pow(2, operand);
			} else if (operand == 4) {
				denominator = pow(2, A);
			} else if (operand == 5) {
				denominator = pow(2, B);
			} else if (operand == 6) {
				denominator = pow(2, C);
			} else {
				std::cout << "Reserved, program not valid" << std::endl;
				IP = operations.size();
				break;
			}
			B = numerator / denominator;
			break;
		}
	case 7:
		{
			uint64_t numerator = A;
			uint64_t denominator = 1;
			if (operand < 4) {
				denominator = pow(2, operand);
			} else if (operand == 4) {
				denominator = pow(2, A);
			} else if (operand == 5) {
				denominator = pow(2, B);
			} else if (operand == 6) {
				denominator = pow(2, C);
			} else {
				std::cout << "Reserved, program not valid" << std::endl;
				IP = operations.size();
				break;
			}
			C = numerator / denominator;
			break;
		}
	default:
		{
			std::cout << "Error opcode " << inst << std::endl;
			IP = operations.size();
			break;
		}
	}
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	vector<uint64_t> operations;
	uint64_t starting = 0;
	int matches = 0;
	queue<uint64_t> testqueue;
	testqueue.push(starting);

	while(getline(infile, buffer, ',')) {
		stringstream ss(buffer);

		uint64_t op;
		ss >> op;

		operations.emplace_back(op);
	}

	while (!testqueue.empty()) {
		uint64_t s = testqueue.front();
		testqueue.pop();
		for (int j = 0; j < 8; j++) {
			bool same = false;
			vector<uint64_t> output;
			vector<uint64_t> secondoutput;
			uint64_t A = s << 3;
			A = A | j;
			uint64_t B = 0;
			uint64_t C = 0;
			uint64_t IP = 0;
			uint64_t binaryLength = ((uint64_t)log2l(A)+1);
			while(IP < operations.size()) {
				compute(operations, A, B, C, IP, output);
			}

			int commons = 0;
			for (int i = 0; i < output.size(); i++) {
				if (output.at(i) != operations.at(operations.size() - output.size() + i)) {
					break;
				}
				commons++;
			}

			if ((commons * 3) == binaryLength) {
				uint64_t next = s << 3;
				next = next | j;
				std::cout << "Found " << commons << " common operations with " << next << std::endl;
				matches = commons;
				testqueue.push(next);
			}
		}
		if (matches == 16) {
			break;
		}
	}
	std::cout << std::dec << "Most matches found " << matches << std::endl;
	return 0;
}
