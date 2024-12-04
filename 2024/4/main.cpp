#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int findXmas(vector<string> map, int xcoord, int ycoord)
{
	int mapxsize = map.at(ycoord).size();
	int mapysize = map.size();
	int xmasfound = 0;
	//Up
	if (ycoord > 2) {
		if (map.at(ycoord-1)[xcoord] == 'M' && map.at(ycoord-2)[xcoord] == 'A' && map.at(ycoord-3)[xcoord] == 'S')
		{
			xmasfound++;
		}
	}

	// Up right
	if (ycoord > 2 && xcoord < mapxsize - 3) {
		if (map.at(ycoord-1)[xcoord+1] == 'M' && map.at(ycoord-2)[xcoord+2] == 'A' && map.at(ycoord-3)[xcoord+3] == 'S')
		{
			xmasfound++;
		}
	}

	// Right
	if (xcoord < mapxsize - 3) {
		if (map.at(ycoord)[xcoord+1] == 'M' && map.at(ycoord)[xcoord+2] == 'A' && map.at(ycoord)[xcoord+3] == 'S')
		{
			xmasfound++;
		}
	}

	// // Down right
	if (ycoord < mapysize - 3 && xcoord < mapxsize - 3) {
		if (map.at(ycoord+1)[xcoord+1] == 'M' && map.at(ycoord+2)[xcoord+2] == 'A' && map.at(ycoord+3)[xcoord+3] == 'S')
		{
			xmasfound++;
		}
	}

	// // Down
	if (ycoord < mapysize - 3) {
		if (map.at(ycoord+1)[xcoord] == 'M' && map.at(ycoord+2)[xcoord] == 'A' && map.at(ycoord+3)[xcoord] == 'S')
		{
			xmasfound++;
		}
	}

	// // Down left
	if (ycoord < mapysize - 3 && xcoord > 2) {
		if (map.at(ycoord+1)[xcoord-1] == 'M' && map.at(ycoord+2)[xcoord-2] == 'A' && map.at(ycoord+3)[xcoord-3] == 'S')
		{
			xmasfound++;
		}
	}

	// // Left
	if (xcoord > 2) {
		if (map.at(ycoord)[xcoord-1] == 'M' && map.at(ycoord)[xcoord-2] == 'A' && map.at(ycoord)[xcoord-3] == 'S')
		{
			xmasfound++;
		}
	}

	// // Up left
	if (ycoord > 2 && xcoord > 2) {
		if (map.at(ycoord-1)[xcoord-1] == 'M' && map.at(ycoord-2)[xcoord-2] == 'A' && map.at(ycoord-3)[xcoord-3] == 'S')
		{
			xmasfound++;
		}
	}

	return xmasfound++;
}

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
    int totalxmas = 0;

	while(getline(infile, buffer)) {
        map.emplace_back(buffer);
	}

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map.at(i).size(); j++) {
			if (map.at(i)[j] == 'X') {
				totalxmas += findXmas(map, j, i);
			}
		}
	}

	std::cout << "Total xmas words found " << totalxmas << std::endl;

	return 0;
}
