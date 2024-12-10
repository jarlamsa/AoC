#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;

int countTrails(std::vector<string> map, int currenty, int currentx, int currentnumber, int maxx, int maxy, std::set<pair<int,int>> &foundEnds)
{
	if(currentnumber == 9) {
		//std::cout << "Found end" << std::endl;
		foundEnds.insert(make_pair(currentx, currenty));
		return 1;
	}

	int trails = 0;
	// Check left
	if (currentx > 0 && map.at(currenty)[currentx-1] == currentnumber + 1 + '0') {
		//std::cout << "Found " << currentnumber+1 << " from left" << std::endl;
		trails += countTrails(map, currenty, currentx-1, currentnumber+1, maxx, maxy, foundEnds);
	}
	// Check right
	if (currentx < maxx && map.at(currenty)[currentx+1] == currentnumber + 1 + '0') {
		//std::cout << "Found " << currentnumber+1 << " from right" << std::endl;
		trails += countTrails(map, currenty, currentx+1, currentnumber+1, maxx, maxy, foundEnds);
	}
	// Check up
	if (currenty > 0 && map.at(currenty-1)[currentx] == currentnumber + 1 + '0') {
		//std::cout << "Found " << currentnumber+1 << " from up" << std::endl;
		trails += countTrails(map, currenty-1, currentx, currentnumber+1, maxx, maxy, foundEnds);
	}
	// Check down
	if (currenty < maxy && map.at(currenty+1)[currentx] == currentnumber + 1 + '0') {
		//std::cout << "Found " << currentnumber+1 << " from down" << std::endl;
		trails += countTrails(map, currenty+1, currentx, currentnumber+1, maxx, maxy, foundEnds);
	}

	// if (currentnumber == 0) {
	// 	std::cout << "Found " << trails << " trails from coords (" << currentx << "," << currenty << ")" << std::endl;
	// }
	return trails;
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	vector<string> map;
	int trails = 0;
	int trailscore = 0;

	while(getline(infile, buffer)) {
        map.emplace_back(buffer);
	}

	int maxx = map.at(0).size()-1;
	int maxy = map.size()-1;

	for(int i = 0; i < map.size(); i++) {
		for(int j = 0; j < map.at(0).size(); j++) {
			if (map.at(i)[j] == '0') {
				std::set<pair<int,int>> foundEnds;
				trails += countTrails(map, i, j, 0, maxx, maxy, foundEnds);
				trailscore += foundEnds.size();
			} 
		}
	}

	cout << "Total trails " << trails << endl;
	return 0;
}
