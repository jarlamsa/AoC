#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <map>
#include <utility>
#include <queue>

using namespace std;
using namespace std::chrono;

typedef std::pair<int64_t, int64_t> intpair;
struct step {
    int64_t row;
    int64_t col;
    int64_t amount_left;
};

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
	vector<string> gmap;
    uint64_t sum = 0;
    std::map<intpair, int64_t> values;
    queue<struct step> steps;

	while(getline(infile, buffer)) {
		gmap.push_back(buffer);
	}

	uint32_t startrow = 0;
	uint32_t startcol = 0;

	for (int64_t i = 0; i < gmap.size(); i++) {
		size_t pos = gmap.at(i).find_first_of('S');
		if (pos != string::npos) {
			startrow = i;
			startcol = pos;
		}
	}

    struct step s;
    s.row = startrow;
    s.col = startcol;
    s.amount_left = 65 + 131;
    steps.push(s);

    while (!steps.empty()) {
        struct step ss;
        ss = steps.front();
        steps.pop();
        std::pair<int64_t,int64_t> p{ss.row,ss.col};
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
        int64_t row = abs(ss.row) % 131;
        int64_t row_above = row - 1;
        if (row_above == -1) {
            row_above = 130;
        }
        int64_t col = abs(ss.col) % 131;
        int64_t col_left = col - 1;
        if (col_left == -1) {
            col_left = 130;
        }
        //cout << "Row " << row << " col " << col << endl;
        if (gmap.at(row_above)[col] != '#') {
            struct step news;
            news.row = ss.row-1;
            news.col = ss.col;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
        if (gmap.at((row+1) % 131 )[col] != '#') {
            struct step news;
            news.row = ss.row+1;
            news.col = ss.col;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
        if (gmap.at(row)[col_left] != '#') {
            struct step news;
            news.row = ss.row;
            news.col = ss.col-1;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
        if (gmap.at(row)[(col+1) % 131] != '#') {
            struct step news;
            news.row = ss.row;
            news.col = ss.col+1;
            news.amount_left = ss.amount_left - 1;
            steps.push(news);
        }
    }

    for(auto i : values) {
        pair<int64_t,int64_t> p = i.first;
        sum += i.second;
    }

    // For this part, when we step 65 times, we are on the edges of the first map.
    // The map size is 131*131 and the paths are traversed 202 300 similar maps to each direction
    // Paths per middle part we get after 65 steps, store this, it is the diamond shape
    // There are 404599 full maps in the horizontal line crossing
    // By experimenting, we see clearly that there is a clear pattern. With each 131 steps, the amount of paths grows a certain amount which also grows certain amount

    // Increases oscillate between 33452 and 33435
    // Start counting after expanding map 65 + 131 steps

    uint64_t increment = 66147;

    for (int i = 1; i < 202298; i++) {
        sum += increment;
        if(i % 2 == 0) {
            increment += 33435;
        } else {
            increment += 33452;
        }
        cout << sum << endl;
    } 

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Plots reachable with 64 steps: " << sum << " time taken " << duration.count() << " us" << endl;
}
