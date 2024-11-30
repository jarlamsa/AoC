#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <map>
#include <utility>
#include <queue>

using namespace std;
using namespace std::chrono;

typedef std::pair<int, int> intpair;
struct step {
    int row;
    int col;
    int amount_left;
};

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
	vector<string> gmap;
    uint64_t sum = 0;
    std::map<intpair, int> values;
    queue<struct step> steps;

	while(getline(infile, buffer)) {
		gmap.push_back(buffer);
	}

	uint32_t startrow = 0;
	uint32_t startcol = 0;

	for (int i = 0; i < gmap.size(); i++) {
		size_t pos = gmap.at(i).find_first_of('S');
		if (pos != string::npos) {
			startrow = i;
			startcol = pos;
		}
	}

    struct step s;
    s.row = startrow;
    s.col = startcol;
    s.amount_left = 64;
    steps.push(s);

    while (!steps.empty()) {
        struct step ss;
        ss = steps.front();
        steps.pop();
        std::pair<int,int> p{ss.row,ss.col};
        if (values.find(p) != values.end()) {
            continue;
        }
        if (ss.amount_left % 2 == 0) {
            values[p] = 1;
        } else {
            values[p] = 0;
        }
        if (ss.amount_left == 0) {
            continue;
        }
        if (ss.row > 0 && gmap.at(ss.row-1)[ss.col] != '#') {
            struct step news;
            news.row = ss.row-1;
            news.col = ss.col;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
        if (ss.row < gmap.size() - 1 && gmap.at(ss.row+1)[ss.col] != '#') {
            struct step news;
            news.row = ss.row+1;
            news.col = ss.col;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
        if (ss.col > 0 && gmap.at(ss.row)[ss.col-1] != '#') {
            struct step news;
            news.row = ss.row;
            news.col = ss.col-1;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
        if (ss.col < gmap.at(0).size() - 1 && gmap.at(ss.row)[ss.col+1] != '#') {
            struct step news;
            news.row = ss.row;
            news.col = ss.col+1;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
    }

    for(auto i : values) {
        pair<int,int> p = i.first;
        sum += i.second;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Plots reachable with 64 steps: " << sum << " time taken " << duration.count() << " us" << endl;
}
