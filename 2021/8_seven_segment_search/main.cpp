#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct segment_info{
	vector<string> input;
	vector<string> output;
};

int main() {
	ifstream infile("input.txt");
	vector<segment_info> segments;
	string line;

	while(getline(infile, line)) {
		size_t pos = line.find('|');
		string input = line.substr(0,pos);
		string output = line.substr(pos+1);

		stringstream inputstream(input);
		stringstream outputstream(output);

		struct segment_info segment;
		string buffer;

		while(inputstream.good()) {
			inputstream >> buffer;
			segment.input.push_back(buffer);
		}
		while(outputstream.good()) {
			outputstream >> buffer;
			segment.output.push_back(buffer);
		}
		segments.push_back(segment);
	}
	uint64_t distinguished = 0;
	for(auto s : segments) {
		for(auto o : s.output) {
			size_t len = o.length();
			if(len == 2 || len == 3 || len == 4 || len == 7) {
				distinguished++;
			}
		}
	}

	cout << "Number of distinguished values " << distinguished << endl;
}