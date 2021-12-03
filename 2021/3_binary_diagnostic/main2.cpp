#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
	ifstream infile("input.txt");
	vector<string> reports;
	int oxy = 0, co2 = 0;
	while(infile.good()) {
		string report;
		infile >> report;
		reports.push_back(report);
	}
	vector<string> co2reports(reports);

	for(int i = 0; i < 12; i++) {
		if(reports.size() == 1) {
			cout << "Found oxygen" << endl;
			break;
		}
		int ones = 0;
		int zeros = 0;
		for(auto r : reports) {
			if(r.at(i) == '1') {
				ones++;
			} else {
				zeros++;
			}
		}
		for(auto it = reports.begin(); it != reports.end(); ) {
			if(ones >= zeros) {
				if((*it).at(i) == '0') {
					it = reports.erase(it);
				} else {
					it++;
				}
			} else {
				if((*it).at(i) == '1') {
					it = reports.erase(it);
				} else {
					it++;
				}
			}
		}
	}

	string oxygenstr = reports.at(0);
	cout << "oxygen " << oxygenstr << endl;

	for(int i = 0; i < 12; i++) {
		if(co2reports.size() == 1) {
			cout << "Found co2" << endl;
			break;
		}
		int ones = 0;
		int zeros = 0;
		for(auto r : co2reports) {
			if(r.at(i) == '1') {
				ones++;
			} else {
				zeros++;
			}
		}
		for(auto it = co2reports.begin(); it != co2reports.end(); ) {
			if(ones < zeros) {
				if((*it).at(i) == '0') {
					it = co2reports.erase(it);
				} else {
					it++;
				}
			} else {
				if((*it).at(i) == '1') {
					it = co2reports.erase(it);
				} else {
					it++;
				}
			}
		}
	}

	string co2string = co2reports.at(0);
	cout << "co2    " << co2string << endl;

	oxy = stoi(oxygenstr, 0, 2);
	co2 = stoi(co2string, 0 ,2);
 
	cout << "oxy " << oxy << " co2 " << co2 << " product " << oxy * co2 << endl;
}