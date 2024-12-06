#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
	vector<string> traversemap;
	int currentX = 0;
	int currentY = 0;
	int row = 0;
    // 1 left, 2 up, 3 right, 4 down
    int direction = 2;

	while(getline(infile, buffer)) {
        string dots(buffer.size(), '.');
        map.push_back(buffer);
        traversemap.push_back(dots);
        size_t startPos = buffer.find('^');
        if (startPos != string::npos)  {
            currentX = startPos;
            currentY = row;
        }
        row++;
	}
	int maxX = traversemap.at(0).size() - 1;
	int maxY = traversemap.size() - 1;

	while (true) {
		traversemap.at(currentY)[currentX] = 'X';
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
	}

	int traversed = 0;
	for (auto s : traversemap) {
		std::cout << s << std::endl;
		traversed += std::count(s.begin(), s.end(), 'X');
	}

	std::cout << "Traversed " << traversed << " number of positions" << std::endl;
}
