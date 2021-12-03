#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
	ifstream infile("input.txt");
	vector<string> reports;
	int gamma_rate = 0, epsilon_rate = 0;
	while(infile.good()) {
		string report;
		infile >> report;
		reports.push_back(report);
	}

	for(int i = 0; i < 12; i++) {
		int ones = 0;
		int zeros = 0;
		for(auto r : reports) {
			if(r.at(i) == '1') {
				ones++;
			} else {
				zeros++;
			}
		}
		if(ones > zeros) {
			gamma_rate |= 1 << 11 - i;
		} else {
			epsilon_rate |= 1 << 11 -i;
		}
	}
	
	cout << "gamma = " << bitset<16>(gamma_rate) << endl;
	cout << "epsilon = " << bitset<16>(epsilon_rate) << endl;

	cout << "product " << gamma_rate * epsilon_rate << endl;
}