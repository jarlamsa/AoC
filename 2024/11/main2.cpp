#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

void blink(std::map<uint64_t, uint64_t> &stones)
{
	std::vector<pair<uint64_t, uint64_t>> currentstones;
	for(auto s : stones) {
		if (s.second > 0) {
			currentstones.emplace_back(make_pair(s.first, s.second));
		}
	}

	for(auto &s : currentstones) {
		uint64_t length = log10l(s.first) + 1;
		stones[s.first] -= s.second;
		if(s.first == 0) {
			stones[1] += s.second;
		} else if (length %2 == 0) {
			uint64_t left = s.first / (pow(10,length/2));
			uint64_t right = s.first - (left*pow(10,length/2));
			stones[left] += s.second;
			stones[right] += s.second;
		} else {
			stones[s.first*2024] += s.second;
		}
	}
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	std::map<uint64_t, uint64_t> stones;

	while(getline(infile, buffer)) {
		stringstream ss(buffer);

		while(!ss.eof()) {
			uint64_t stone;
			ss >> stone;
			stones[stone]++;
		}
	}

	for(int i = 0; i < 75; i++) {
		blink(stones);
	}

	uint64_t numstones = 0;
	for(auto s : stones) {
		numstones += s.second;
	}

	cout << "Number of stones after 75 blinks " << numstones << endl;
	return 0;
}
