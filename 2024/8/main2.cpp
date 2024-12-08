#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

void makeAntinodeMap(std::map<char,std::vector<std::pair<int, int>>> &antennas, std::vector<string> &antinodeMap)
{
	for (const auto& [key, coords] : antennas) {
		for (int i = 0; i < coords.size() - 1; i++) {
			for (int j = i+1; j < coords.size(); j++) {
				int diffy = coords.at(i).first - coords.at(j).first;
				int diffx = coords.at(i).second - coords.at(j).second;

				int anty = coords.at(i).first + diffy;
				int antx = coords.at(i).second + diffx;

				while (anty >= 0 && anty < antinodeMap.size() && antx >= 0 && antx < antinodeMap.at(0).size()) {
					antinodeMap.at(anty)[antx] = '#';
					anty += diffy;
					antx += diffx;
				}

				anty = coords.at(i).first - diffy;
				antx = coords.at(i).second - diffx;

				while (anty >= 0 && anty < antinodeMap.size() && antx >= 0 && antx < antinodeMap.at(0).size()) {
					antinodeMap.at(anty)[antx] = '#';
					anty -= diffy;
					antx -= diffx;
				}

				anty = coords.at(j).first + diffy;
				antx = coords.at(j).second + diffx;

				while (anty >= 0 && anty < antinodeMap.size() && antx >= 0 && antx < antinodeMap.at(0).size()) {
					antinodeMap.at(anty)[antx] = '#';
					anty += diffy;
					antx += diffx;
				}

				anty = coords.at(i).first - diffy;
				antx = coords.at(i).second - diffx;

				while (anty >= 0 && anty < antinodeMap.size() && antx >= 0 && antx < antinodeMap.at(0).size()) {
					antinodeMap.at(anty)[antx] = '#';
					anty -= diffy;
					antx -= diffx;
				}
			}
		}
	}

}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	vector<string> antennaMap;
	vector<string> antinodeMap;
	std::map<char, std::vector<std::pair<int, int>>> antennas;
	int row = 0;
	int antinodeCount = 0;

	while(getline(infile, buffer)) {
        string dots(buffer.size(), '.');
        antennaMap.push_back(buffer);
        antinodeMap.push_back(dots);
		for (int i = 0; i < buffer.size(); i++) {
			if (buffer[i] != '.') {
				antennas[buffer[i]].emplace_back(make_pair(row, i));
			}
		}
		row++;
	}

	makeAntinodeMap(antennas, antinodeMap);

	std::cout << "Antenna map" << std::endl;
	for (auto s : antennaMap) {
		std::cout << s << std::endl;
	}

	std::cout << "Antinode map" << std::endl;
	for (auto s : antinodeMap) {
		std::cout << s << std::endl;
		antinodeCount += std::count(s.begin(), s.end(), '#');
	}

    for (const auto& [key, value] : antennas) {
        std::cout << '[' << key << "] = ";
		for (auto v : value) {
			std::cout << "(" << v.first << ", " << v.second << ") ";
		}
		std::cout << std::endl;
	}

	std::cout << "Found " << antinodeCount << " antinodes" << std::endl;  

	return 0;
}
