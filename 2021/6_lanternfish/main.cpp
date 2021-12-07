#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	vector<int> lanterfishes;
	ifstream infile("input.txt");

	string line;
	while(getline(infile, line, ',')) {
		lanterfishes.push_back(stoi(line));
	}

	for(int i = 0; i < 80; i++) {
		int spawn = 0;
		for(int& l : lanterfishes) {
			if(l == 0) {
				l = 6;
				spawn++;
			} else {
				l--;
			}
		}
		for(int i = 0; i < spawn; i++) {
			lanterfishes.push_back(8);
		}
	}
	cout << "After 80 days there is " << lanterfishes.size() << " fishes" << endl;
	return 0;
}