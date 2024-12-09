#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

uint64_t calculateChecksum(std::vector<uint64_t> blocks)
{
	uint64_t result = 0;
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks.at(i) != -1)
		{
			result += i * blocks.at(i);
		} else {
			break;
		}
	}
	return result;
}

void makeBlockPresentation(string disk_map, std::vector<uint64_t> &blocks)
{
	uint32_t id = 0;
	uint32_t length = 0;
	bool file = true;

	for (int i = 0; i < disk_map.size(); i++) {
		length = disk_map[i] - '0';
		for (int j = 0; j < length; j++) {
			if (file) {
				blocks.emplace_back(id);
			} else {
				blocks.emplace_back(-1);
			}
		}
		if (file == true) {
			id++;
		}
		file = !file;
	}

}

void compress(std::vector<uint64_t> &blocks)
{
	//auto lastPos;
	//auto firstPos;
	while(true) {
		auto backIterator = blocks.end() - 1;
		auto frontIterator = blocks.begin() - 1;
		for (; backIterator >= blocks.begin(); backIterator--) {
			if (*backIterator != -1)
				break;
		}
		for (;frontIterator != blocks.end(); frontIterator++) {
			if (frontIterator == backIterator) {
				return;
			}
			if (*frontIterator == -1)
				break;
		}
		iter_swap(frontIterator, backIterator);
	}
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	uint64_t checksum = 0;

	while(getline(infile, buffer)) {
		stringstream ss(buffer);
	}
	std::vector<uint64_t> blocks;
	makeBlockPresentation(buffer, blocks);
	compress(blocks);
	// for (auto b : blocks) {
	// 	std::cout << b << " ";
	// }
	std::cout << std::endl;
	checksum = calculateChecksum(blocks);

	cout << "checksum of the filesystem " << checksum << endl;
	return 0;
}
