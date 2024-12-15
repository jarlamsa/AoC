#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Check if we can move vertically from current, this call uses recursion
bool canMoveVertically(std::vector<string> &map, int currentx, int currenty, int direction)
{
	bool canMove = true;
	bool dualMove = false;
	if (map.at(currenty)[currentx] == '[' || map.at(currenty)[currentx] == ']') {
		dualMove = true;
	}

	if (!dualMove) {
		if ((direction == 2 && map.at(currenty-1)[currentx] == '.') ||
			(direction == 4 && map.at(currenty+1)[currentx] == '.')) {
			return true;
		}

		if ((direction == 2 && map.at(currenty-1)[currentx] == '#') ||
			(direction == 4 && map.at(currenty+1)[currentx] == '#')) {
			return false;
		}

		if ((direction == 2 && (map.at(currenty-1)[currentx] == '[' || map.at(currenty-1)[currentx] == ']'))) {
			return canMoveVertically(map, currentx, currenty-1, 2);
		}

		if ((direction == 4 && (map.at(currenty+1)[currentx] == '[' || map.at(currenty+1)[currentx] == ']'))) {
			return canMoveVertically(map, currentx, currenty+1, 4);
		}

		std::cout << "ERROR: shouldn't come here" << std::endl;
		return false;
	}

	// Up
	if (direction == 2) {
		if (map.at(currenty)[currentx] == '[') {
			if (map.at(currenty-1)[currentx] == '.' && map.at(currenty-1)[currentx+1] == '.') {
				return true;
			}

			if (map.at(currenty-1)[currentx] == '#' || map.at(currenty-1)[currentx+1] == '#') {
				return false;
			}

			if (map.at(currenty-1)[currentx] == '[' || map.at(currenty-1)[currentx] == ']') {
				if(!canMoveVertically(map, currentx, currenty-1, 2)) {
					return false;
				}
			}

			if (map.at(currenty-1)[currentx+1] == '[' || map.at(currenty-1)[currentx+1] == ']') {
				if(!canMoveVertically(map, currentx+1, currenty-1, 2)) {
					return false;
				}
			}
		} else if (map.at(currenty)[currentx] == ']') {
			if (map.at(currenty-1)[currentx] == '.' && map.at(currenty-1)[currentx-1] == '.') {
				return true;
			}

			if (map.at(currenty-1)[currentx] == '#' || map.at(currenty-1)[currentx-1] == '#') {
				return false;
			}

			if (map.at(currenty-1)[currentx] == '[' || map.at(currenty-1)[currentx] == ']') {
				if(!canMoveVertically(map, currentx, currenty-1, 2)) {
					return false;
				}
			}

			if (map.at(currenty-1)[currentx-1] == '[' || map.at(currenty-1)[currentx-1] == ']') {
				if(!canMoveVertically(map, currentx-1, currenty-1, 2)) {
					return false;
				}
			}
		}
	}

	// Down
	if (direction == 4) {
		if (map.at(currenty)[currentx] == '[') {
			if (map.at(currenty+1)[currentx] == '.' && map.at(currenty+1)[currentx+1] == '.') {
				return true;
			}

			if (map.at(currenty+1)[currentx] == '#' || map.at(currenty+1)[currentx+1] == '#') {
				return false;
			}

			if (map.at(currenty+1)[currentx] == '[' || map.at(currenty+1)[currentx] == ']') {
				if(!canMoveVertically(map, currentx, currenty+1, 4)) {
					return false;
				}
			}

			if (map.at(currenty+1)[currentx+1] == '[' || map.at(currenty+1)[currentx+1] == ']') {
				if(!canMoveVertically(map, currentx+1, currenty+1, 4)) {
					return false;
				}
			}
		} else if (map.at(currenty)[currentx] == ']') {
			if (map.at(currenty+1)[currentx] == '.' && map.at(currenty+1)[currentx-1] == '.') {
				return true;
			}

			if (map.at(currenty+1)[currentx] == '#' || map.at(currenty+1)[currentx-1] == '#') {
				return false;
			}

			if (map.at(currenty+1)[currentx] == '[' || map.at(currenty+1)[currentx] == ']') {
				if(!canMoveVertically(map, currentx, currenty+1, 4)) {
					return false;
				}
			}

			if (map.at(currenty+1)[currentx-1] == '[' || map.at(currenty+1)[currentx-1] == ']') {
				if(!canMoveVertically(map, currentx-1, currenty+1, 4)) {
					return false;
				}
			}
		}
	}
	return true;
}

void moveVertically(std::vector<string> &map, int currentx, int currenty, int direction)
{
	bool dualMove = false;
	if (map.at(currenty)[currentx] == '[' || map.at(currenty)[currentx] == ']') {
		dualMove = true;
	}

	if (!dualMove) {
		if (direction == 2 && (map.at(currenty-1)[currentx] == ']' || map.at(currenty-1)[currentx] == '[')) {
			moveVertically(map, currentx, currenty-1, direction);
		}

		if (direction == 4 && (map.at(currenty+1)[currentx] == ']' || map.at(currenty+1)[currentx] == '[')) {
			moveVertically(map, currentx, currenty+1, direction);
		}
		if (direction == 2 && map.at(currenty-1)[currentx] == '.') {
			map.at(currenty-1)[currentx] = map.at(currenty)[currentx];
			map.at(currenty)[currentx] = '.';
			return;
		}

		if (direction == 4 && map.at(currenty+1)[currentx] == '.') {
			char temp = map.at(currenty)[currentx];
			map.at(currenty)[currentx] = map.at(currenty+1)[currentx];
			map.at(currenty+1)[currentx] = temp;
			return;
		}
	}

	// Up
	if (direction == 2) {
		if (map.at(currenty)[currentx] == '[') {
			if (map.at(currenty-1)[currentx] == '[' || map.at(currenty-1)[currentx] == ']') {
				moveVertically(map, currentx, currenty-1, 2);
			}

			if (map.at(currenty-1)[currentx+1] == '[') {
				moveVertically(map, currentx+1, currenty-1, 2);
			}
			char temp = map.at(currenty-1)[currentx];
			map.at(currenty-1)[currentx] = map.at(currenty)[currentx];
			map.at(currenty)[currentx] = temp;

			temp = map.at(currenty-1)[currentx+1];
			map.at(currenty-1)[currentx+1] = map.at(currenty)[currentx+1];
			map.at(currenty)[currentx+1] = temp;
		} else if (map.at(currenty)[currentx] == ']') {
			if (map.at(currenty-1)[currentx] == '[' || map.at(currenty-1)[currentx] == ']') {
				moveVertically(map, currentx, currenty-1, 2);
			}

			if (map.at(currenty-1)[currentx-1] == ']') {
				moveVertically(map, currentx-1, currenty-1, 2);
			}
			char temp = map.at(currenty-1)[currentx];
			map.at(currenty-1)[currentx] = map.at(currenty)[currentx];
			map.at(currenty)[currentx] = temp;

			temp = map.at(currenty-1)[currentx-1];
			map.at(currenty-1)[currentx-1] = map.at(currenty)[currentx-1];
			map.at(currenty)[currentx-1] = temp;
		}

		return;
	}

	// Down
	if (direction == 4) {
		if (map.at(currenty)[currentx] == '[') {
			if (map.at(currenty+1)[currentx] == '[' || map.at(currenty+1)[currentx] == ']') {
				moveVertically(map, currentx, currenty+1, 4);
			}

			if (map.at(currenty+1)[currentx+1] == '[') {
				moveVertically(map, currentx+1, currenty+1, 4);
			}
			char temp = map.at(currenty+1)[currentx];
			map.at(currenty+1)[currentx] = map.at(currenty)[currentx];
			map.at(currenty)[currentx] = temp;

			temp = map.at(currenty+1)[currentx+1];
			map.at(currenty+1)[currentx+1] = map.at(currenty)[currentx+1];
			map.at(currenty)[currentx+1] = temp;
		} else if (map.at(currenty)[currentx] == ']') {
			if (map.at(currenty+1)[currentx] == '[' || map.at(currenty+1)[currentx] == ']') {
				moveVertically(map, currentx, currenty+1, 4);
			}

			if (map.at(currenty+1)[currentx-1] == ']') {
				moveVertically(map, currentx-1, currenty+1, 4);
			}
			char temp = map.at(currenty+1)[currentx];
			map.at(currenty+1)[currentx] = map.at(currenty)[currentx];
			map.at(currenty)[currentx] = temp;

			temp = map.at(currenty+1)[currentx-1];
			map.at(currenty+1)[currentx-1] = map.at(currenty)[currentx-1];
			map.at(currenty)[currentx-1] = temp;
		}

		return;
	}	
}

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
		if (canMoveVertically(map, currentx, currenty, direction)) {
			moveVertically(map, currentx, currenty, direction);
			currenty--;
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
		if (canMoveVertically(map, currentx, currenty, direction)) {
			moveVertically(map, currentx, currenty, direction);
			currenty++;
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
			string map_row;
			for (auto c : buffer) {
				if (c == '#') {
					map_row.append("##");
				} else if (c == 'O') {
					map_row.append("[]");
				} else if (c == '@') {
					map_row.append("@.");
				} else if (c == '.') {
					map_row.append("..");
				}
			}
			map.push_back(map_row);
			string::size_type n = map_row.find('@');
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

	for (auto s : map) {
		std::cout << s << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map.at(i).size(); j++) {
			if (map.at(i)[j] == '[') {
				coordinate_sum += (100 * i + j);
			}
		} 
	}

	std::cout << "Coordinate sum is " << coordinate_sum << std::endl;

	return 0;
}
