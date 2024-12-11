#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

void blink(std::list<uint64_t> &stones)
{
	for(auto it = stones.begin(); it != stones.end(); it++) {
		uint64_t length = log10l(*it) + 1;
		if(*it == 0) {
			*it = 1;
		} else if (length %2 == 0) {
			uint64_t left = *it / (pow(10,length/2));
			uint64_t right = *it - (left*pow(10,length/2));
			*it = left;
			it++;
			stones.insert(it, right);
			it--;
		} else {
			*it *= 2024;
		}
	}
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	std::list<uint64_t> stones;

	while(getline(infile, buffer)) {
		stringstream ss(buffer);

		while(!ss.eof()) {
			uint64_t stone;
			ss >> stone;
			stones.push_back(stone);
		}
	}

	for(int i = 0; i < 25; i++) {
		blink(stones);
	}

	cout << "Number of stones after 25 blinks " << stones.size() << endl;
	return 0;
}
