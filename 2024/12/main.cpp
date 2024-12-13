#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct region {
	uint32_t area = 0;
	uint32_t perimeter = 0;
	char id;
	// Store coordinates of each of the plots in region
	std::vector<pair<uint32_t, uint32_t>> coordinates;
};

bool isInRegion(char id, std::pair<uint32_t, uint32_t> coords, std::vector<struct region> regions)
{
	for (auto r : regions) {
		if (id == r.id) {
			if (std::find(r.coordinates.begin(), r.coordinates.end(), coords) != r.coordinates.end()) {
				return true;
			}
		}
	}

	return false;
}

void formRegion(struct region &r, std::vector<string> map, uint32_t currentx, uint32_t currenty)
{
	// Add current plot to the area and coordinates
	r.area++;
	r.coordinates.emplace_back(currentx,currenty);
	//std::cout << "Adding (" << currentx << "," << currenty << ") to the region " << r.id << std::endl;

	// Check left if it is in same region
	if (currentx > 0 && map.at(currenty)[currentx-1] == r.id) {
		// Check if it has been added yet to region
		if (std::find(r.coordinates.begin(), r.coordinates.end(), make_pair(currentx-1,currenty)) == r.coordinates.end()) {
			//std::cout << "Grow area to the left from (" << currentx << "," << currenty << ")" << std::endl;
			formRegion(r, map, currentx-1, currenty);
		}
	} else {
		r.perimeter++;
	}

	// Check right
	if (currentx < map.at(0).size() - 1 && map.at(currenty)[currentx+1] == r.id) {
		// Check if it has been added yet to region
		if (std::find(r.coordinates.begin(), r.coordinates.end(), make_pair(currentx+1,currenty)) == r.coordinates.end()) {
			//std::cout << "Grow area to the right from (" << currentx << "," << currenty << ")" << std::endl;
			formRegion(r, map, currentx+1, currenty);
		}
	} else {
		r.perimeter++;
	}

	// Check up
	if (currenty > 0 && map.at(currenty-1)[currentx] == r.id) {
		// Check if it has been added yet to region
		if (std::find(r.coordinates.begin(), r.coordinates.end(), make_pair(currentx,currenty-1)) == r.coordinates.end()) {
			//std::cout << "Grow area to the up from (" << currentx << "," << currenty << ")" << std::endl;
			formRegion(r, map, currentx, currenty-1);
		}
	} else {
		r.perimeter++;
	}

	// Check down
	if (currenty < map.size() - 1 && map.at(currenty+1)[currentx] == r.id) {
		// Check if it has been added yet to region
		if (std::find(r.coordinates.begin(), r.coordinates.end(), make_pair(currentx,currenty+1)) == r.coordinates.end()) {
			//std::cout << "Grow area to the down from (" << currentx << "," << currenty << ")" << std::endl;
			formRegion(r, map, currentx, currenty+1);
		}
	} else {
		r.perimeter++;
	}
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	std::vector<string> map;
	std::vector<struct region> regions;
	uint32_t price;

	while(getline(infile, buffer)) {
		map.emplace_back(buffer);
	}

	for (uint32_t i = 0; i < map.size(); i++) {
		for (uint32_t j = 0; j < map.at(i).size(); j++) {
			if (!isInRegion(map.at(i)[j], make_pair(j, i), regions)) {
				//std::cout << "Create new region with ID " << map.at(i)[j] << std::endl;
				struct region r;
				r.id = map.at(i)[j];
				formRegion(r, map, j, i);
				regions.push_back(r);
			}
		}
	}

	for (auto r : regions) {
		//std::cout << "Found region " << r.id << " with area of " << r.area << " and with perimeter of " << r.perimeter << std::endl;
		price += r.area * r.perimeter;
	}

	cout << "Total price of fencing " << price << endl;
	return 0;
}
