#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
	ifstream infile("input.txt");

	string buffer;
	vector<int> lefts;
	vector<int> rights;
	int total_diff = 0;

	while(getline(infile, buffer)) {
		stringstream ss(buffer);

		int left, right;
		ss >> left;
		ss >> right;

		lefts.emplace_back(left);
		rights.emplace_back(right);
	}

	std::sort(lefts.begin(), lefts.end());
	std::sort(rights.begin(), rights.end());

	for (int i = 0; i < lefts.size(); i++) {
		total_diff += abs(lefts.at(i) - rights.at(i));
	}

	cout << "Total differences in sorted lists is " << total_diff << endl;
	return 0;
}
