#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	vector<int> numbers;
	int product = 0;

	ifstream infile("input.txt");
	while(infile.good()) {
		int num;
		infile >> num;
		numbers.push_back(num);
	}
	bool found = false;
	for(auto i : numbers) {
		for(auto j : numbers) {
			for(auto k : numbers) {
				if(j+i+k == 2020) {
					product = i*j*k;
					found = true;
					break;
				}
			}
		}
		if(found)
			break;
	}

	cout << "Product " << product << endl;
}