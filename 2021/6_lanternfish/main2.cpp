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

	uint64_t calendar[9] = {0};
	for(auto l : lanterfishes) {
		calendar[l]++;
	}

	for(int i = 0; i < 256; i++) {
		int day = i%7;
		//cout << "It is day " << day << endl;;
		uint64_t spawn = calendar[day];
		calendar[day] += calendar[7];
		calendar[7] = calendar[8];
		calendar[8] = spawn;
	}
	uint64_t sum = 0;
	for(int i = 0; i < 9; i++) {
		sum += calendar[i];
	}

	cout << "After 256 days there is " << sum << " fishes" << endl;
	return 0;
}