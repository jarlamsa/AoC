#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

void compute(vector<uint32_t> &operations, uint64_t &A, uint64_t &B, uint64_t &C, uint64_t &IP, vector<uint32_t> &output)
{
	uint32_t inst = operations.at(IP);
	uint32_t operand = operations.at(IP+1);
	IP += 2;

	//std::cout << "A: " << A << " B: " << B << " C: " << C << std::endl;
	//std::cout << "op " << inst << " oper " << operand << " IP " << IP << std::endl;

	switch (inst)
	{
	//adv
	case 0:
		{
			uint32_t numerator = A;
			uint32_t denominator = 1;
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
			uint32_t result = 0;
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
			uint32_t result = 0;
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
			uint32_t numerator = A;
			uint32_t denominator = 1;
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
			uint32_t numerator = A;
			uint32_t denominator = 1;
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
	vector<uint32_t> operations;
	vector<uint32_t> output;
	uint64_t A = 41644071;
	uint64_t B = 0;
	uint64_t C = 0;

	uint64_t IP = 0;

	while(getline(infile, buffer, ',')) {
		stringstream ss(buffer);

		uint32_t op;
		ss >> op;

		operations.emplace_back(op);
	}

	while(IP < operations.size()) {
		compute(operations, A, B, C, IP, output);
	}

	for (auto o : output) {
		std::cout << o << ",";
	}
	std::cout << std::endl;
	return 0;
}
