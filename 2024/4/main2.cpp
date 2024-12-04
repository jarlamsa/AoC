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

	if (xcoord == 0 || ycoord == 0 || xcoord == mapxsize-1 || ycoord == mapxsize-1)
	{
		return 0;
	}

	if (((map.at(ycoord-1)[xcoord-1] == 'M' && map.at(ycoord+1)[xcoord+1] == 'S') ||
		(map.at(ycoord-1)[xcoord-1] == 'S' && map.at(ycoord+1)[xcoord+1] == 'M')) &&
		((map.at(ycoord-1)[xcoord+1] == 'M' && map.at(ycoord+1)[xcoord-1] == 'S') ||
		(map.at(ycoord-1)[xcoord+1] == 'S' && map.at(ycoord+1)[xcoord-1] == 'M'))  ) {
			return 1;
	}

	return 0;
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
			if (map.at(i)[j] == 'A') {
				totalxmas += findXmas(map, j, i);
			}
		}
	}

	std::cout << "Total xmas words found " << totalxmas << std::endl;

	return 0;
}
