#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

struct system_equation
{
	int64_t x1;
	int64_t x2;
	int64_t y1;
	int64_t y2;
	int64_t c;
	int64_t d;
	int64_t a;
	int64_t b;
};

bool solve(struct system_equation &eq)
{
	int64_t det = (eq.x1 * eq.y2) - (eq.y1 * eq.x2);
	eq.a = ((eq.c * eq.y2) - (eq.d * eq.x2)) / det;
	eq.b = ((eq.x1 * eq.d) - (eq.y1 * eq.c)) / det;

	if (eq.a > 100 || eq.b > 100 || eq.a < 0 || eq.b < 0) {
		return false;
	}
	return true;
}

int main()
{
	ifstream infile("input.txt");

	string buffer;
	uint64_t tokens = 0;
	uint64_t solvable = 0;

	while(getline(infile, buffer)) {
		string::size_type startpos = buffer.find("Button A: ");
		if (startpos != string::npos) {
			regex params("(\\d+)[A-Za-z,+ ]+(\\d+)");
			regex prize("(\\d+), Y=(\\d+)");
			smatch m;
			regex_search(buffer, m, params);
			struct system_equation e;
			e.x1 = stoi(m.str(1));
			e.y1 = stoi(m.str(2));

			// Get b parameters
			getline(infile, buffer);
			regex_search(buffer, m, params);
			e.x2 = stoi(m.str(1));
			e.y2 = stoi(m.str(2));

			// Get prize
			getline(infile, buffer);
			regex_search(buffer, m, prize);
			e.c = stoi(m.str(1));
			e.d = stoi(m.str(2));

			if (solve(e)) {
				solvable++;
				if (((e.x1 * e.a) + (e.x2 * e.b)) == e.c && ((e.y1 * e.a) + (e.y2 * e.b)) == e.d)
					tokens += e.a * 3 + e.b * 1;
			}
		}
	}

	std::cout << "Needed tokens " << tokens << ", equations solved " << solvable << std::endl;
}
