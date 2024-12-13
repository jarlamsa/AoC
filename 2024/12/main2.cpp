#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct region {
	uint32_t area = 0;
	uint32_t perimeter = 0;
	uint32_t sides = 0;
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
	uint8_t sides = 0;
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
		sides |= 0x01;
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
		sides |= 0x02;
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
		sides |= 0x04;
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
		sides |= 0x08;
	}

	// Outer corners
	if (sides != 0x00 || sides != 0x0c || sides != 0x03) {
		if (sides == 0x05 || sides == 0x09 || sides == 0x06 || sides == 0x0a) {
			//std::cout << "Corner " << (int)sides << " in (" << currentx << "," << currenty << ")" << std::endl;
			r.sides += 1;
		} else if (sides == 0x07 || sides == 0x0b || sides == 0x0d || sides == 0x0e) {
			//std::cout << "Endpoint " << (int)sides << " in (" << currentx << "," << currenty << ")" << std::endl;
			r.sides += 2;
		} else if (sides == 0x0f) {
			r.sides += 4;
		}
	}

	// Inner corners
	// Upper left
	//std::cout << "Checking inner corner with " << (int) sides << " in (" << currentx << "," << currenty << ")" << std::endl;
	//std::cout << "Binary anding lower right " << (int) (sides & 0x0a) << std::endl;
	if (currentx > 0 && currenty > 0 && ((int)(sides & 0x05) == 0) && map.at(currenty-1)[currentx-1] != r.id) {
		//std::cout << "Inner corner1 " << (int)sides << " in (" << currentx << "," << currenty << ")" << std::endl;
		r.sides += 1;
	}
	// Upper right
	if (currentx < map.at(0).size()-1 && currenty > 0 && ((int)(sides & 0x06) == 0) && map.at(currenty-1)[currentx+1] != r.id) {
		//std::cout << "Inner corner2 " << (int)sides << " in (" << currentx << "," << currenty << ")" << std::endl;
		r.sides += 1;
	}
	// Lower left
	if (currentx > 0 && currenty < map.size() - 1 && ((int)(sides & 0x09) == 0) && map.at(currenty+1)[currentx-1] != r.id) {
		//std::cout << "Inner corner3 " << (int)sides << " in (" << currentx << "," << currenty << ")" << std::endl;
		r.sides += 1;
	}
	// Lower right
	if (currentx < map.at(0).size()-1 && currenty < map.size() - 1 && ((int)(sides & 0x0a) == 0) && map.at(currenty+1)[currentx+1] != r.id) {
		//std::cout << "Inner corner4 " << (int)sides << " in (" << currentx << "," << currenty << ")" << std::endl;
		r.sides += 1;
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
		std::cout << "Found region " << r.id << " with area of " << r.area << " and with sides " << r.sides << std::endl;
		price += r.area * r.sides;
	}

	cout << "Total price of fencing " << price << endl;
	return 0;
}
