#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main() {
	ifstream infile("input.txt");

	string line;
	int illegal_score = 0;
	while(getline(infile, line)) {
		stack<char> expected;
		char illegal = 0;
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
				illegal = line.at(i);
				break;
			}
			if(expected.top() != line.at(i)) {
				illegal = line.at(i);
				break;
			} else {
				expected.pop();
			}
		}
		if(illegal == ')')
			illegal_score += 3;
		if(illegal == ']')
			illegal_score += 57;
		if(illegal == '}')
			illegal_score += 1197;
		if(illegal == '>')
			illegal_score += 25137;
	}

	cout << "Total illegal score " << illegal_score << endl;
}