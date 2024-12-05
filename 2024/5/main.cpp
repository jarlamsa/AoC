#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

bool checkRules(std::map<int,vector<int>> &rules, std::vector<int> &row)
{
	for(int i = 0; i < row.size() - 1; i++) {
		//std::cout << "Checking " << row.at(i);
		if (rules.find(row.at(i)) == rules.end()) {
			continue;
		}
		vector<int> r = rules[row.at(i)];
		
		for(auto rule : r) {
			for(int j = i + 1; j < row.size(); j++) {
				if (row.at(j) == rule) {
					return false;
				}
			}
		}
	}

	return true;
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	std::map<int, vector<int>> rules;
	bool read_rules = true;
	int sum = 0;

	while(getline(infile, buffer)) {
		if(buffer.empty()) {
			read_rules = false;
			continue;
		}

		if (read_rules) {
			stringstream ss(buffer);

			string left, right;
			getline(ss, left, '|' );
			getline(ss, right);
			int leftpage = stoi(left);
			int rightpage = stoi(right);

			// Page not found
			if (rules.find(rightpage) == rules.end()) {
				vector<int> v;
				v.emplace_back(leftpage);
				rules[rightpage] = v;
			} else {
				rules[rightpage].emplace_back(leftpage);
			}

		} else {
			std::vector<int> row;
			std::cout << buffer << std::endl;
			stringstream ss(buffer);
			string page;
			while(getline(ss, page, ',')) {
				row.emplace_back(stoi(page));
			}
			bool rulesok = checkRules(rules, row);
			if(rulesok) {
				//std::cout << "OK" << std::endl;
				int middle_element = row.at(row.size() / 2);
				std::cout << "Middle element " << middle_element << std::endl;
				sum += middle_element;
			} else {
				//std::cout << "NOK" << std::endl;
			}
		}
	}

	std::cout << "Sum of middle elements of correct rows is " << sum << std::endl;

    // for (const auto& [key, value] : rules) {
    //     std::cout << '[' << key << "] = ";
	// 	for (auto v : value) {
	// 		std::cout << v << ", ";
	// 	}
	// }
	return 0;
}
