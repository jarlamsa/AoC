#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;


void moveRobot(std::vector<string> &map, int &currentx, int &currenty, int direction)
{
	// left
	if (direction == 1) {
		for (int i = currentx-1; i > 0; i--) {
			if (map.at(currenty)[i] == '#')
				break;
			if (map.at(currenty)[i] == '.') {
				currentx--;
				while (i <= currentx) {
					char temp = map.at(currenty)[i];
					map.at(currenty)[i] = map.at(currenty)[i+1];
					map.at(currenty)[i+1] = temp;
					i++;
				}
				break;
			}
		}
	}
	// up
	else if (direction == 2) {
		for (int i = currenty-1; i > 0; i--) {
			if (map.at(i)[currentx] == '#')
				break;
			if (map.at(i)[currentx] == '.') {
				currenty--;
				while (i <= currenty) {
					char temp = map.at(i)[currentx];
					map.at(i)[currentx] = map.at(i+1)[currentx];
					map.at(i+1)[currentx] = temp;
					i++;
				}
				break;
			}
		}
	}
	// right
	else if (direction == 3) {
		for (int i = currentx+1; i < map.at(0).size(); i++) {
			if (map.at(currenty)[i] == '#')
				break;
			if (map.at(currenty)[i] == '.') {
				currentx++;
				while (i >= currentx) {
					char temp = map.at(currenty)[i];
					map.at(currenty)[i] = map.at(currenty)[i-1];
					map.at(currenty)[i-1] = temp;
					i--;
				}
				break;
			}
		}
	}
	// down
	else if (direction == 4) {
		for (int i = currenty+1; i < map.size(); i++) {
			if (map.at(i)[currentx] == '#')
				break;
			if (map.at(i)[currentx] == '.') {
				currenty++;
				while (i >= currenty) {
					char temp = map.at(i)[currentx];
					map.at(i)[currentx] = map.at(i-1)[currentx];
					map.at(i-1)[currentx] = temp;
					i--;
				}
				break;
			}
		}
	}
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	std::vector<string> map;
	std::vector<int> moves;
	bool reading_map = true;
	int currentx = 0;
	int currenty = 0;
	int row = 0;
	int coordinate_sum = 0;

	while(getline(infile, buffer)) {
		if(buffer.empty()) {
			reading_map = false;
		} else if (reading_map) {
			map.push_back(buffer);
			string::size_type n = buffer.find('@');
			if (n != string::npos) {
				currenty = row;
				currentx = n;
			}
			row++;
		} else {
			for (auto c : buffer) {
				if (c == '<') {
					moves.push_back(1);
				} else if (c == '^') {
					moves.push_back(2);
				} else if (c == '>') {
					moves.push_back(3);
				} else if (c == 'v') {
					moves.push_back(4);
				}
			}
		}
	}

	for (auto s : map) {
		std::cout << s << std::endl;
	}

	for (auto m : moves) {
		moveRobot(map, currentx, currenty, m);
	}

	std::cout << "After moves" << std::endl;

	for (auto s : map) {
		std::cout << s << std::endl;
	}

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map.at(i).size(); j++) {
			if (map.at(i)[j] == 'O') {
				coordinate_sum += (100 * i + j);
			}
		} 
	}

	std::cout << "Coordinate sum is " << coordinate_sum << std::endl;

	return 0;
}
