#include <iostream>
#include <fstream>

using namespace std;

#define SIZE_X 100
#define SIZE_Y 100

int main() {
	ifstream infile("input.txt");
	int heightmap[SIZE_Y][SIZE_X] = {0};

	char c;
	for(int i = 0; i < SIZE_Y; i++) {
		for(int j = 0; j < SIZE_X; j++) {
			infile >> c;
			heightmap[i][j] = c - '0';
		}
	}
	uint64_t risklevel = 0;
	uint64_t heightmaps = 0;
	for(int i = 0; i < SIZE_Y; i++) {
		for(int j = 0; j < SIZE_X; j++) {
			//Upper left corner
			if(i == 0 && j == 0) {
				if(heightmap[i][j] < heightmap[i+1][j] && heightmap[i][j] < heightmap[i][j+1]) {
					cout << "Found1" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Upmost row
			if(i == 0 && j > 0 && j < SIZE_X-1) {
				if(heightmap[i][j] < heightmap[i][j-1] && heightmap[i][j] < heightmap[i+1][j] && heightmap[i][j] < heightmap[i][j+1]) {
					cout << "Found2" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Upper right corner
			if(i == 0 && j == SIZE_X-1) {
				if(heightmap[i][j] < heightmap[i+1][j] && heightmap[i][j] < heightmap[i][j-1]) {
					cout << "Found3" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Left column
			if(i > 0 && i < SIZE_Y-1 && j == 0) {
				if(heightmap[i][j] < heightmap[i-1][j] && heightmap[i][j] < heightmap[i+1][j] && heightmap[i][j] < heightmap[i][j+1]) {
					cout << "Found4" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Center
			if(i > 0 && i < SIZE_Y-1 && j > 0 && j < SIZE_X-1) {
				if(heightmap[i][j] < heightmap[i-1][j] && heightmap[i][j] < heightmap[i+1][j] && 
				   heightmap[i][j] < heightmap[i][j+1] && heightmap[i][j] < heightmap[i][j-1]) {
					//cout << "Found5" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Right column
			if(i > 0 && i < SIZE_Y-1 && j == SIZE_X-1) {
				if(heightmap[i][j] < heightmap[i-1][j] && heightmap[i][j] < heightmap[i][j-1] && heightmap[i][j] < heightmap[i+1][j]) {
					cout << "Found6" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Lower left corner
			if(i == SIZE_Y-1 && j == 0) {
				if(heightmap[i][j] < heightmap[i-1][j] && heightmap[i][j] < heightmap[i][j+1]) {
					cout << "Found7" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Bottom row
			if(i == SIZE_Y-1 && j > 0 && j < SIZE_X-1) {
				if(heightmap[i][j] < heightmap[i][j-1] && heightmap[i][j] < heightmap[i-1][j] && heightmap[i][j] < heightmap[i][j+1]) {
					cout << "Found8" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
			//Lower right corner
			if(i == SIZE_Y-1 && j == SIZE_X-1) {
				if(heightmap[i][j] < heightmap[i-1][j] && heightmap[i][j] < heightmap[i][j-1]) {
					cout << "Found9" << " " << i << " " << j << " " << heightmap[i][j] << endl;
					risklevel++;
					risklevel += heightmap[i][j];
					heightmaps += heightmap[i][j];
					continue;
				}
			}
		}
	}
	cout << "Total risk level: " << risklevel << endl;
	cout << "Coming from heights: " << heightmaps << endl;	
}