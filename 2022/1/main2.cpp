#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp_function(int i, int j) { return (i>j); }

int main()
{
	vector<int> calories;
	ifstream infile("input.txt");

	string buffer;
	int total_calories = 0;
	int topthree_cals = 0;

	while(getline(infile, buffer)) {
		if(buffer.empty()) {
			calories.push_back(total_calories);
			total_calories = 0;
			continue;
		}
		int cal = stoi(buffer);
		total_calories += cal;
	}

	//Sort the calorie counts and count only the three highest
	sort(calories.begin(), calories.end(), cmp_function);

	calories.resize(3);
	for (auto c : calories) {
		topthree_cals += c;
	}

	cout << "Top three elves have " << topthree_cals << " calories" << endl;
	return 0;
}
