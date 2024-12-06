#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool checkLooping(vector<string> &map, int currentX, int currentY, int direction)
{
	int traversemap[130][130];
	for (int i = 0; i < 130; i++) {
		for (int j = 0; j < 130; j++) {
			traversemap[i][j] = 0;
		}
	}
	while (true) {
		// Only mark the traverse once to spot looping
		traversemap[currentY][currentX]++;
		// Check if we are going outside
		if ((direction == 1 && currentX == 0) ||
			(direction == 2 && currentY == 0) ||
			(direction == 3 && currentX == map.at(0).size()-1) ||
			(direction == 4 && currentY == map.size()-1)) {
				break;
		}
		// Check next step if it contains obstacle
		if (direction == 1) {
			if (map.at(currentY)[currentX-1] == '#') {
				direction++;
			} else {
				currentX--;
			}
		} else if (direction == 2) {
			if (map.at(currentY-1)[currentX] == '#') {
				direction++;
			} else {
				currentY--;
			}
		} else if (direction == 3) {
			if (map.at(currentY)[currentX+1] == '#') {
				direction++;
			} else {
				currentX++;
			}
		} else {
			if (map.at(currentY+1)[currentX] == '#') {
				direction = 1;
			} else {
				currentY++;
			}
		}

		// If we have already traversed this node in same direction, there is a loop
		if (traversemap[currentY][currentX] > 4) {
			return true;
		}
	}
	return false;
}

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
	vector<string> traversemap;
	int currentX = 0;
	int currentY = 0;
	int startingX = 0;
	int startingY = 0;
	int startDir = 2;
	int row = 0;
    // 1 left, 2 up, 3 right, 4 down
    int direction = 2;
	int loops = 0;

	while(getline(infile, buffer)) {
        string dots(buffer.size(), '.');
        map.push_back(buffer);
        traversemap.push_back(dots);
        size_t startPos = buffer.find('^');
        if (startPos != string::npos)  {
            currentX = startPos;
            currentY = row;
			startingX = startPos;
			startingY = row;
        }
        row++;
	}
	int maxX = traversemap.at(0).size() - 1;
	int maxY = traversemap.size() - 1;

	while (true) {
		traversemap.at(currentY)[currentX] = '0' + direction;
		// Check if we are going outside
		if ((direction == 1 && currentX == 0) ||
			(direction == 2 && currentY == 0) ||
			(direction == 3 && currentX == maxX) ||
			(direction == 4 && currentY == maxY)) {
				break;
		}
		// Check next step if it contains obstacle
		if (direction == 1) {
			if (map.at(currentY)[currentX-1] == '#') {
				direction++;
			} else if (map.at(currentY)[currentX-1] == '.') {
				map.at(currentY)[currentX-1] = '#';
				if (checkLooping(map, startingX, startingY, 2)) {
					map.at(currentY)[currentX-1] = 'O';
				} else {
					map.at(currentY)[currentX-1] = '.';
				}

				currentX--;
			} else {
				currentX--;
			}
		} else if (direction == 2) {
			if (map.at(currentY-1)[currentX] == '#') {
				direction++;
			} else if (map.at(currentY-1)[currentX] == '.') {
				map.at(currentY-1)[currentX] = '#';
				if (checkLooping(map, startingX, startingY, 2)) {
					map.at(currentY-1)[currentX] = 'O';
				} else {
					map.at(currentY-1)[currentX] = '.';
				}
				currentY--;
			} else {
				currentY--;
			}
		} else if (direction == 3) {
			if (map.at(currentY)[currentX+1] == '#') {
				direction++;
			} else if (map.at(currentY)[currentX+1] == '.') {
				map.at(currentY)[currentX+1] = '#';
				if (checkLooping(map, startingX, startingY, 2)) {
					map.at(currentY)[currentX+1] = 'O';
				} else {
					map.at(currentY)[currentX+1] = '.';
				}
				currentX++;
			} else {
				currentX++;
			}
		} else {
			if (map.at(currentY+1)[currentX] == '#') {
				direction = 1;
			} else if (map.at(currentY+1)[currentX] == '.') {
				map.at(currentY+1)[currentX] = '#';
				if (checkLooping(map, startingX, startingY, 2)) {
					map.at(currentY+1)[currentX] = 'O';
				} else {
					map.at(currentY+1)[currentX] = '.';
				}
				currentY++;
			} else {
				currentY++;
			}
		}
 	}

	for (auto s : traversemap) {
		std::cout << s << std::endl;
	}

	for (auto s : map) {
		std::cout << s << std::endl;
		loops += std::count(s.begin(), s.end(), 'O');
	}

	std::cout << "Found " << loops << " places where putting obstacle would make guard to loop forever" << std::endl;
}
