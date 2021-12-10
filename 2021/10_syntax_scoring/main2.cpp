#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream infile("input.txt");

	string line;
	vector<uint64_t> autocompletion_scores;
	while(getline(infile, line)) {
		stack<char> expected;
		bool illegal = 0;
		uint64_t row_score = 0;
		for(int i = 0; i < line.size(); i++) {
			if(line.at(i) == '(') {
				expected.push(')');
				continue;
			}
			if(line.at(i) == '<') {
				expected.push('>');
				continue;
			}
			if(line.at(i) == '[') {
				expected.push(']');
				continue;
			}
			if(line.at(i) == '{') {
				expected.push('}');
				continue;
			}
			
			if(expected.empty()) {
				illegal = true;
				break;
			}
			if(expected.top() != line.at(i)) {
				illegal = true;
				break;
			} else {
				expected.pop();
			}
		}
		if(illegal)
			continue;
		while(!expected.empty()) {
			row_score *=5;
			if(expected.top() == ')')
				row_score += 1;
			if(expected.top() == ']')
				row_score += 2;
			if(expected.top() == '}')
				row_score += 3;
			if(expected.top() == '>')
				row_score += 4;
			expected.pop();
		}
		autocompletion_scores.push_back(row_score);
	}

	sort(autocompletion_scores.begin(), autocompletion_scores.end());
	cout << "Number of autocompletion scores " << autocompletion_scores.size() << endl;

	for(auto i : autocompletion_scores) {
		cout << i << endl;
	}

	int median = autocompletion_scores.size() / 2;
	cout << "Median score " << autocompletion_scores.at(median) << endl;
}