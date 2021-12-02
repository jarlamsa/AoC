#include <iostream>
#include <fstream>

using namespace std;

int main() {
	int position = 0;
	int depth = 0;

	ifstream input("input.txt");

	while(input.good()) {
		string dir;
		int amount;
		input >> dir;
		input >> amount;
		if(dir.compare("forward") == 0) {
			position += amount;
		} else if(dir.compare("down") == 0) {
			depth += amount;
		} else if(dir.compare("up") == 0) {
			depth -= amount;
		}
	}

	cout << "Final position " << position << " at depth " << depth << endl;
	cout << "Multiplied " << position * depth << endl;
}