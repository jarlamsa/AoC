#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define SIZE_X 100
#define SIZE_Y 100

void basin_neighbours(int (&heightmap)[SIZE_Y][SIZE_X], int i, int j, int num, int *size) {
	cout << "Neighbours for " << i << " " << j << " " << *size << endl;
	heightmap[i][j] = num;
	*size +=1;
	if(i > 0) {
		if(heightmap[i-1][j] != num && heightmap[i-1][j] != 9)
			basin_neighbours(heightmap, i-1, j, num, size);
	}
	if(j > 0) {
		if(heightmap[i][j-1] != num && heightmap[i][j-1] != 9)
			basin_neighbours(heightmap, i, j-1, num, size);
	}
	if(i < SIZE_Y-1) {
		if(heightmap[i+1][j] != num && heightmap[i+1][j] != 9)
			basin_neighbours(heightmap, i+1, j, num, size);
	}
	if(j < SIZE_X-1) {
		if(heightmap[i][j+1] != num && heightmap[i][j+1] != 9)
			basin_neighbours(heightmap, i, j+1, num, size);
	}
}

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
	
	int basin = -1;
	int one, two, three = 0;

	for(int i = 0; i < SIZE_Y; i++) {
		for(int j = 0; j < SIZE_X; j++) {
			if(heightmap[i][j] >= 0 && heightmap[i][j] != 9) {
				int size = 0;
				basin_neighbours(heightmap, i, j, basin, &size);
				basin--;
				cout << "Size was " << size << endl;
				if(size > one) {
					three = two;
					two = one;
					one = size;
				} else if(size > two) {
					three = two;
					two = size;
				} else if(size > three) {
					three = size;
				}
			}
		}
	}

	cout << "Product of largest basins " << one * two * three << endl;
	return 0;
}