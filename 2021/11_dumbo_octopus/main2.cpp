#include <iostream>
#include <fstream>

using namespace std;

#define MAP_SIZE 10

struct octopus_map{
	int power_level[MAP_SIZE][MAP_SIZE] = {0};
	bool flashed[MAP_SIZE][MAP_SIZE] = {0};
};

void printmap(struct octopus_map o_map){
	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			cout << o_map.power_level[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void increase_power(struct octopus_map& o_map) {
	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			o_map.power_level[i][j]++;
		}
	}
}

void flash_octopus(struct octopus_map& o_map, int i, int j) {
	if(i > 0)
		o_map.power_level[i-1][j]++;
	if(j > 0)
		o_map.power_level[i][j-1]++;
	if(j > 0 && i > 0)
		o_map.power_level[i-1][j-1]++;
	if(i < MAP_SIZE-1 && j > 0)
		o_map.power_level[i+1][j-1]++;
	if(i > 0 && j < MAP_SIZE-1)
		o_map.power_level[i-1][j+1]++;
	if(i < MAP_SIZE-1)
		o_map.power_level[i+1][j]++;
	if(j < MAP_SIZE-1)
		o_map.power_level[i][j+1]++;
	if(i < MAP_SIZE-1 && j < MAP_SIZE-1)
		o_map.power_level[i+1][j+1]++;
}

int flash_map(struct octopus_map& o_map) {
	int ret = 0;

	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			if(o_map.power_level[i][j] > 9 && o_map.flashed[i][j] == false) {
				flash_octopus(o_map, i, j);
				o_map.flashed[i][j] = true;
				ret++;
			}
		}
	}
	return ret;
}

void reset_map(struct octopus_map& o_map) {
	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			if(o_map.power_level[i][j] > 9) {
				o_map.power_level[i][j] = 0;
				o_map.flashed[i][j] = false;
			}
		}
	}
}

//void 

int main() {
	ifstream infile("input.txt");
	struct octopus_map o_map;
	string line;
	int i = 0;
	while(getline(infile, line)) {
		for(int j = 0; j < line.size(); j++) {
			o_map.power_level[i][j] = line.at(j) - '0';
		}
		i++;
	}
	printmap(o_map);
	uint64_t flashes = 0;
	for(int steps = 0; steps < 1000; steps++) {
		increase_power(o_map);
		int ret = 0;
		int step_flashes = 0;
		do {
			ret = flash_map(o_map);
			step_flashes += ret;

		} while (ret != 0);
		reset_map(o_map);
		printmap(o_map);
		if(step_flashes == 100) {
			cout << "All octopi flashed at " << steps+1 << endl;
			break;
		}
	}
}