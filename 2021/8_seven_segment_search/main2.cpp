#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct segment_info{
	string input[10];
	string output[4];
	int decoded[10];
	int dec_output;
};

string find_encoded(struct segment_info si, int number) {
	for(int i = 0; i < 10; i++) {
		if(si.decoded[i] == number)
			return si.input[i];
	}
	cout << "No match found" << endl;
	return "abcdefgh";
}

int find_decoded(struct segment_info si, string encoded) {
	for(int i = 0; i < 10; i++) {
		size_t input_size = si.input[i].size();
		size_t enc_size = encoded.size();
		if(input_size != enc_size)
			continue;

		bool found = true;
		for(int j = 0; j < input_size; j++) {
			size_t pos = encoded.find(si.input[i].at(j));
			if(pos == string::npos) {
				found = false;
				break;
			}
		}
		if(found)
			return si.decoded[i];
	}
	cout << "No match found" << endl;
	return -1;
}

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
		int i = 0;
		while(inputstream.good()) {
			inputstream >> buffer;
			segment.input[i] = buffer;
			i++;
		}
		i = 0;
		while(outputstream.good()) {
			outputstream >> buffer;
			segment.output[i] = buffer;
			i++;
		}
		fill_n(segment.decoded, 10, -1);
		segments.push_back(segment);
	}

	//Decode all the numbers
	for(auto& s : segments) {
		//Find the 4 unique ones
		for(int i = 0; i < 10; i++) {
			size_t len = s.input[i].size();
			if(len == 2)
				s.decoded[i] = 1;
			if(len == 3)
				s.decoded[i] = 7;
			if(len == 4)
				s.decoded[i] = 4;
			if(len == 7)
				s.decoded[i] = 8;
		}
		//Find number 3 with help of 1
		string buff = find_encoded(s, 1);
		for(int i = 0; i < 10; i++) {
			bool found = true;
			size_t len = s.input[i].size();
			if(len == 5) {
				for(int j = 0; j < buff.size(); j++) {
					size_t pos = s.input[i].find(buff.at(j));
					if(pos == string::npos) {
						found = false;
						break;
					}
				}
				if(found) {
					s.decoded[i] = 3;
				}
			}
		}
		//Find number 9 with help of 3
		buff = find_encoded(s, 3);
		for(int i = 0; i < 10; i++) {
			bool found = true;
			size_t len = s.input[i].size();
			if(len == 6) {
				for(int j = 0; j < buff.size(); j++) {
					size_t pos = s.input[i].find(buff.at(j));
					if(pos == string::npos) {
						found = false;
						break;
					}
				}
				if(found) {
					s.decoded[i] = 9;
				}
			}
		}
		//Find number 0 with help of 1 as 9 is found already
		buff = find_encoded(s, 1);
		for(int i = 0; i < 10; i++) {
			if(s.decoded[i] != -1)
				continue;
			bool found = true;
			size_t len = s.input[i].size();
			if(len == 6) {
				for(int j = 0; j < buff.size(); j++) {
					size_t pos = s.input[i].find(buff.at(j));
					if(pos == string::npos) {
						found = false;
						break;
					}
				}
				if(found) {
					s.decoded[i] = 0;
				}
			}
		}
		//Find number 5 with help of 4
		buff = find_encoded(s, 4);
		for(int i = 0; i < 10; i++) {
			if(s.decoded[i] != -1)
				continue;
			int found = 0;
			size_t len = s.input[i].size();
			if(len == 5) {
				for(int j = 0; j < buff.size(); j++) {
					size_t pos = s.input[i].find(buff.at(j));
					if(pos != string::npos) {
						found++;
					}
				}
				if(found == 3) {
					s.decoded[i] = 5;
				}
			}
		}
		//Rest are unique
		for(int i = 0; i < 10; i++) {
			if(s.decoded[i] != -1)
				continue;
			size_t len = s.input[i].size();
			if(len == 5)
				s.decoded[i] = 2;
			if(len == 6)
				s.decoded[i] = 6;
		}
	}

	for(auto& s : segments) {
		string output;
		for(int i = 0; i < 4; i++) {
			cout << s.output[i] << endl;
			output += to_string(find_decoded(s, s.output[i]));
		}
		s.dec_output = stoi(output);
		cout << s.dec_output << endl;
	}

	int sum = 0;
	for(auto s : segments) {
		sum += s.dec_output;
	}

	cout << "Decoded output sum " << sum << endl;
}