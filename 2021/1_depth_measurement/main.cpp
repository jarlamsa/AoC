#include <iostream>
#include <fstream>


using namespace std;

int main() {
	ifstream infile("input.txt");
	int increases = 0;
	int depth = 0;
	infile >> depth;

	while(infile.good()) {
		int cur_depth;
		infile >> cur_depth;
		if(cur_depth > depth)
			increases++;
		depth = cur_depth;
	}
	cout << "depth increased " << increases << " times" << endl;
}