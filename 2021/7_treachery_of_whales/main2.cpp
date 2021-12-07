#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	vector<int> crabs;

	ifstream infile("input.txt");

	string buffer;

	while(getline(infile, buffer, ',')) {
		crabs.push_back(stoi(buffer));
	}

	int max_value = 0;

	for(auto c : crabs) {
		if(c > max_value)
			max_value = c;
	}

	
	uint64_t min_fuel = 0xffffffffffffffff;
	int min_step = 0;

	for(int i = 1; i < max_value; i++) {
		uint64_t fuel = 0;

		for(auto c: crabs) {
			if(c > i) {
				for(int j = c - i; j > 0; j--)
					fuel += j;
			} else {
				for(int j = i - c; j > 0; j--)
					fuel += j;
			}
		}

		if(fuel < min_fuel) {
			min_fuel = fuel;
			min_step = i;
		}
	}

	cout << "Minimum fuel usage: " << min_fuel << " for step " << min_step << endl;
}