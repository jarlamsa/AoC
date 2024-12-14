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
	int seconds = 0;

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

	simulate(robots, 81, 101, 103);
	seconds = 81;

	// Simulate 101 after every keypress, christmas tree is visible after 7858 seconds
	while (true) {
		simulate(robots, 101, 101, 103);
		seconds += 101;
		std::vector<string> map;
		string dots(101, '.');
		for (int i = 0; i < 103; i++) {
			map.push_back(dots);
		}

		for (auto r : robots) {
			if(map.at(r.y)[r.x] == '.') {
				map.at(r.y)[r.x] = '#';
			}
		}

		for (auto s : map) {
			std::cout << s << std::endl;
		}
		std::cout << "After " << seconds << " seconds" << std::endl;
		getchar();
	}

	return 0;
}
