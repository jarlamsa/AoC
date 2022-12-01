#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream infile("input.txt");

	string buffer;
	int total_calories = 0;
	int most_calories = 0;

	while(getline(infile, buffer)) {
		if(buffer.empty()) {
			most_calories = max(total_calories, most_calories);
			total_calories = 0;
			continue;
		}
		int cal = stoi(buffer);
		total_calories += cal;
	}

	cout << "Elf with most calories is having " << most_calories << " calories" << endl;
	return 0;
}
