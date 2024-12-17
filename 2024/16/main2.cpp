#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

#define MAP_SIZE 141

struct node {
	int row;
	int col;
	int distance = INT_MAX;
	int direction = 0;
};

struct node_comp {
	bool operator()(struct node const& n1, struct node const& n2)
	{
		return n1.distance > n2.distance;
	}
};

int main()
{
	ifstream infile("input.txt");

	string buffer;
	vector<string> map;
	int row = 0;
	int currentx = 0;
	int currenty = 0;
	int endx = 0;
	int endy = 0;
	// 1 = left, 2 = up, 3 right, 4 down
	int currentDir = 2;

	int distance[MAP_SIZE][MAP_SIZE][5];
	bool visited[MAP_SIZE][MAP_SIZE][5] = {false};
	priority_queue<struct node, vector<struct node>, node_comp> Q;

	int enddistance[MAP_SIZE][MAP_SIZE][5];
	bool endvisited[MAP_SIZE][MAP_SIZE][5] = {false};

	while(getline(infile, buffer)) {
		map.emplace_back(buffer);
		string::size_type n = buffer.find('S');
		if (n != string::npos) {
			currenty = row;
			currentx = n;
			struct node nd;
			nd.row = row;
			nd.col = n;
			nd.distance = 0;
			nd.direction = 3;
			Q.push(nd);
		}
		n = buffer.find('E');
		if (n != string::npos) {
			endy = row;
			endx = n;
		}
		row++;
	}

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			for (int l = 0; l < 5; l++) {
				if (i == currenty && j == currentx) {
					distance[i][j][l] = 0;
				} else {
					distance[i][j][l] = INT_MAX;
				}
			}
		}
	}

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			for (int l = 0; l < 5; l++) {
				if (i == endy && j == endx) {
					enddistance[i][j][l] = 0;
				} else {
					enddistance[i][j][l] = INT_MAX;
				}
			}
		}
	}

	while (!Q.empty()) {
		struct node n = Q.top();
		Q.pop();
		visited[n.row][n.col][n.direction] = true;

		// Check up
		if (n.row > 0 && map.at(n.row-1)[n.col] != '#' && n.direction != 4) {
			if (n.direction == 2) {
				if (!visited[n.row-1][n.col][2] && n.distance + 1 < distance[n.row-1][n.col][2]) {
					distance[n.row-1][n.col][2] = n.distance + 1;
					struct node p;
					p.row = n.row-1;
					p.col = n.col;
					p.distance = n.distance + 1;
					p.direction = 2;
					Q.push(p);
				}
			} else {
				if (!visited[n.row-1][n.col][2] && n.distance + 1001 < distance[n.row-1][n.col][2]) {
					distance[n.row][n.col][2] = n.distance + 1000;
					distance[n.row-1][n.col][2] = n.distance + 1001;
					struct node p;
					p.row = n.row-1;
					p.col = n.col;
					p.distance = n.distance + 1001;
					p.direction = 2;
					Q.push(p);
				}
			}
		}


		// Check right
		if (n.col < MAP_SIZE - 1 && map.at(n.row)[n.col+1] != '#' && n.direction != 1) {
			if (n.direction == 3) {
				if (!visited[n.row][n.col+1][3] && n.distance + 1 < distance[n.row][n.col+1][3]) {
					distance[n.row][n.col+1][3] = n.distance + 1;
					struct node p;
					p.row = n.row;
					p.col = n.col+1;
					p.distance = n.distance + 1;
					p.direction = 3;
					Q.push(p);
				}
			} else {
				if (!visited[n.row][n.col+1][3] && n.distance + 1001 < distance[n.row][n.col+1][3]) {
					distance[n.row][n.col][3] = n.distance + 1000;
					distance[n.row][n.col+1][3] = n.distance + 1001;
					struct node p;
					p.row = n.row;
					p.col = n.col+1;
					p.distance = n.distance + 1001;
					p.direction = 3;
					Q.push(p);
				}
			}
		}

		// Check down
		if (n.row < MAP_SIZE - 1 && map.at(n.row+1)[n.col] != '#' && n.direction != 2) {
			if (n.direction == 4) {
				if (!visited[n.row+1][n.col][4] && n.distance + 1 < distance[n.row+1][n.col][4]) {
					distance[n.row+1][n.col][4] = n.distance + 1;
					struct node p;
					p.row = n.row+1;
					p.col = n.col;
					p.distance = n.distance + 1;
					p.direction = 4;
					Q.push(p);
				}
			} else {
				if (!visited[n.row+1][n.col][4] && n.distance + 1001 < distance[n.row+1][n.col][4]) {
					distance[n.row][n.col][4] = n.distance + 1000;
					distance[n.row+1][n.col][4] = n.distance + 1001;
					struct node p;
					p.row = n.row+1;
					p.col = n.col;
					p.distance = n.distance + 1001;
					p.direction = 4;
					Q.push(p);
				}
			}
		}

		// Check left
		if (n.col > 0 && map.at(n.row)[n.col-1] != '#' && n.direction != 3) {
			if (n.direction == 1) {
				if (!visited[n.row][n.col-1][1] && n.distance + 1 < distance[n.row][n.col-1][1]) {
					distance[n.row][n.col-1][1] = n.distance + 1;
					struct node p;
					p.row = n.row;
					p.col = n.col-1;
					p.distance = n.distance + 1;
					p.direction = 1;
					Q.push(p);
				}
			} else {
				if (!visited[n.row][n.col-1][1] && n.distance + 1001 < distance[n.row][n.col-1][1]) {
					distance[n.row][n.col][1] = n.distance + 1000;
					distance[n.row][n.col-1][1] = n.distance + 1001;
					struct node p;
					p.row = n.row;
					p.col = n.col-1;
					p.distance = n.distance + 1001;
					p.direction = 1;
					Q.push(p);
				}
			}
		}
	}

	int32_t minimum = INT_MAX; 

	for (int i = 0; i < 5; i++) {
		minimum = min (minimum, distance[endy][endx][i]);
	}

	cout << "Minimum score at end " << minimum << endl;

	// We are going backwards now so directions are reversed
	struct node nd;
	nd.row = endy;
	nd.col = endx;
	nd.distance = 0;
	nd.direction = 2;
	Q.push(nd);

	while (!Q.empty()) {
		struct node n = Q.top();
		Q.pop();
		endvisited[n.row][n.col][n.direction] = true;

		// Check up
		if (n.row > 0 && map.at(n.row-1)[n.col] != '#' && n.direction != 2) {
			if (n.direction == 4) {
				if (!endvisited[n.row-1][n.col][4] && n.distance + 1 < enddistance[n.row-1][n.col][4]) {
					enddistance[n.row-1][n.col][4] = n.distance + 1;
					struct node p;
					p.row = n.row-1;
					p.col = n.col;
					p.distance = n.distance + 1;
					p.direction = 4;
					Q.push(p);
				}
			} else {
				if (!endvisited[n.row-1][n.col][4] && n.distance + 1001 < enddistance[n.row-1][n.col][4]) {
					enddistance[n.row][n.col][4] = n.distance + 1000;
					enddistance[n.row-1][n.col][4] = n.distance + 1001;
					struct node p;
					p.row = n.row-1;
					p.col = n.col;
					p.distance = n.distance + 1001;
					p.direction = 4;
					Q.push(p);
				}
			}
		}


		// Check right
		if (n.col < MAP_SIZE - 1 && map.at(n.row)[n.col+1] != '#' && n.direction != 3) {
			if (n.direction == 1) {
				if (!endvisited[n.row][n.col+1][1] && n.distance + 1 < enddistance[n.row][n.col+1][1]) {
					enddistance[n.row][n.col+1][1] = n.distance + 1;
					struct node p;
					p.row = n.row;
					p.col = n.col+1;
					p.distance = n.distance + 1;
					p.direction = 1;
					Q.push(p);
				}
			} else {
				if (!endvisited[n.row][n.col+1][1] && n.distance + 1001 < enddistance[n.row][n.col+1][1]) {
					enddistance[n.row][n.col][1] = n.distance + 1000;
					enddistance[n.row][n.col+1][1] = n.distance + 1001;
					struct node p;
					p.row = n.row;
					p.col = n.col+1;
					p.distance = n.distance + 1001;
					p.direction = 1;
					Q.push(p);
				}
			}
		}

		// Check down
		if (n.row < MAP_SIZE - 1 && map.at(n.row+1)[n.col] != '#' && n.direction != 4) {
			if (n.direction == 2) {
				if (!endvisited[n.row+1][n.col][2] && n.distance + 1 < enddistance[n.row+1][n.col][2]) {
					enddistance[n.row+1][n.col][2] = n.distance + 1;
					struct node p;
					p.row = n.row+1;
					p.col = n.col;
					p.distance = n.distance + 1;
					p.direction = 2;
					Q.push(p);
				}
			} else {
				if (!endvisited[n.row+1][n.col][2] && n.distance + 1001 < enddistance[n.row+1][n.col][2]) {
					enddistance[n.row][n.col][2] = n.distance + 1000;
					enddistance[n.row+1][n.col][2] = n.distance + 1001;
					struct node p;
					p.row = n.row+1;
					p.col = n.col;
					p.distance = n.distance + 1001;
					p.direction = 2;
					Q.push(p);
				}
			}
		}

		// Check left
		if (n.col > 0 && map.at(n.row)[n.col-1] != '#' && n.direction != 1) {
			if (n.direction == 3) {
				if (!endvisited[n.row][n.col-1][3] && n.distance + 1 < enddistance[n.row][n.col-1][3]) {
					enddistance[n.row][n.col-1][3] = n.distance + 1;
					struct node p;
					p.row = n.row;
					p.col = n.col-1;
					p.distance = n.distance + 1;
					p.direction = 3;
					Q.push(p);
				}
			} else {
				if (!endvisited[n.row][n.col-1][3] && n.distance + 1001 < enddistance[n.row][n.col-1][3]) {
					enddistance[n.row][n.col][3] = n.distance + 1000;
					enddistance[n.row][n.col-1][3] = n.distance + 1001;
					struct node p;
					p.row = n.row;
					p.col = n.col-1;
					p.distance = n.distance + 1001;
					p.direction = 3;
					Q.push(p);
				}
			}
		}
	}

	int minnodes = 0;

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			bool minpath = false;
			for (int l = 0; l < 5; l++) {
				for (int k = 0; k < 5; k++) {
				//std::cout << "(" << i << "," << j << "," << l << ") distance from start: " << distance[i][j][l] << " from end " << enddistance[i][j][l] << endl;
					if (distance[i][j][l] + enddistance[i][j][k] == minimum) {
						minnodes++;
						minpath = true;
						break;
					}
					if (minpath) break;
				}
			}
			if (minpath) {
				std::cout << '*';
			} else {
				std::cout << map.at(i)[j];
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Number of nodes " << minnodes << std::endl;

	for (int i = 0; i < 5; i++) {
		minimum = min (minimum, enddistance[currenty][currentx][i]);
	}

	cout << "Minimum score at end " << minimum << endl;

}
