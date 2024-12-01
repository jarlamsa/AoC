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
	int similarity_score = 0;

	while(getline(infile, buffer)) {
		stringstream ss(buffer);

		int left, right;
		ss >> left;
		ss >> right;

		lefts.emplace_back(left);
		rights.emplace_back(right);
	}

	for (auto i : lefts) {
		similarity_score += i * std::count(rights.begin(), rights.end(), i);
	}

	cout << "Total similarity score is " << similarity_score << endl;
	return 0;
}
