#include <iostream>
#include <fstream>


using namespace std;

int main() {
	ifstream infile("input.txt");
	int increases = 0;
	int first, second, third = 0;
	int depth = 0;
	infile >> first;
	infile >> second;
	infile >> third;
	depth = first + second + third;

	while(infile.good()) {
		int cur_depth;
		cur_depth = second + third;
		first = second;
		second = third;
		infile >> third;
		cur_depth += third;
		if(cur_depth > depth)
			increases++;
		depth = cur_depth;
	}
	cout << "depth increased " << increases << " times" << endl;
}