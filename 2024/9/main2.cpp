#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>

using namespace std;

struct memblock
{
	uint32_t length;
	uint32_t id;
	uint32_t address;
	bool free_space = false;
};

uint64_t calculateChecksum(std::list<struct memblock> blocks)
{
	uint64_t result = 0;
	for (auto const& block : blocks) {
		if (!block.free_space) {
			for (int j = block.address; j < block.address+block.length; j++) {
				result += j*block.id;
			}
		}
	}
	return result;
}

void makeBlockPresentation(string disk_map, std::list<struct memblock> &blocks)
{
	uint32_t id = 0;
	uint32_t length = 0;
	bool file = true;
	uint32_t address = 0;

	for (int i = 0; i < disk_map.size(); i++) {
		length = disk_map[i] - '0';
		struct memblock memblck;
		memblck.length = length;
		memblck.address = address;
		address += length;
		if (file == true) {
			memblck.id = id;
			id++;
		} else {
			memblck.id = -1;
			memblck.free_space = true;
		}
		blocks.push_back(memblck);

		file = !file;
	}

}

void compress(std::list<struct memblock> &blocks)
{
	auto backIterator = blocks.rbegin();
	for (; backIterator != blocks.rend(); backIterator++) {
		auto frontIterator = blocks.begin();
		if (backIterator->id == -1)
			continue;
		
		for (;frontIterator != blocks.end(); frontIterator++) {
			if (frontIterator->id == backIterator->id) {
				break;
			}
			if (frontIterator->id == -1) {
				// Do the swapping by changing address of the block, no need to do any switching of elements
				if (frontIterator->length >= backIterator->length) {
					backIterator->address = frontIterator->address;
					frontIterator->address += backIterator->length;
					frontIterator->length -= backIterator->length;
					break;
				}
			}
		}
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
	std::list<struct memblock> blocks;
	makeBlockPresentation(buffer, blocks);
	compress(blocks);
	checksum = calculateChecksum(blocks);

	cout << "checksum of the filesystem " << checksum << endl;
	return 0;
}
