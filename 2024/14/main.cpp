#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

struct robot {
	int32_t x;
	int32_t y;
	int32_t velx;
	int32_t vely;
};

void simulate(std::vector<struct robot> &robots, uint32_t steps, uint32_t maxx, uint32_t maxy)
{
	for (auto &r : robots) {
		r.x += r.velx * steps;
		r.y += r.vely * steps;

		r.x += steps * maxx;
		r.y += steps * maxy;
		r.x %= maxx;
		r.y %= maxy;
	}
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	std::vector<struct robot> robots;

	while(getline(infile, buffer)) {
		regex params("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)");
		smatch m;
		regex_search(buffer, m, params);
		struct robot r;
		r.x = stoi(m.str(1));
		r.y = stoi(m.str(2));
		r.velx = stoi(m.str(3));
		r.vely = stoi(m.str(4));
		robots.push_back(r);
	}

	simulate(robots, 100, 101, 103);

	uint32_t quad1 = 0;
	uint32_t quad2 = 0;
	uint32_t quad3 = 0;
	uint32_t quad4 = 0;
	uint32_t halfx = 101/2;
	uint32_t halfy = 103/2;


	for (auto r : robots) {
		if (r.x < halfx && r.y < halfy) {
			quad1++;
		} else if (r.x > halfx && r.y < halfy) {
			quad2++;
		} else if (r.x < halfx && r.y > halfy) {
			quad3++;
		} else if (r.x > halfx && r.y > halfy) {
			quad4++;
		}
	}

	std::cout << "Safety factor " << quad1 * quad2 * quad3 * quad4 << std::endl;

	return 0;
}
