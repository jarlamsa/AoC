#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX_COORD 1000

struct ventline{
	int startx =0 ;
	int starty= 0;
	int endx=0;
	int endy=0;
};

int main() {
	ifstream infile("input.txt");
	int ventmap[MAX_COORD][MAX_COORD] = {0};
	vector<ventline> lines;
	string buffer;

	while(getline(infile, buffer)) {
		struct ventline line;
		size_t pos = buffer.find(',');
		line.startx = stoi(buffer.substr(0, pos));
		line.starty = stoi(buffer.substr(pos+1, buffer.find(' ') - pos));
		pos = buffer.find("->");
		size_t commapos = buffer.find(',', pos);
		line.endx = stoi(buffer.substr(pos+3, commapos - pos+3));
		line.endy = stoi(buffer.substr(commapos+1));
		cout << line.startx << endl;
		lines.push_back(line);
	}

	for(auto l : lines){
		if(l.startx != l.endx && l.starty != l.endy) {
			continue;
		}
		if(l.startx > l.endx)
			swap(l.startx, l.endx);
		if(l.starty > l.endy)
			swap(l.starty, l.endy);
		
		if(l.startx==l.endx) {
			for(int i = l.starty; i <= l.endy; i++) {
				ventmap[i][l.startx]++;
			}
		}
		if(l.starty == l.endy) {
			for(int i = l.startx; i <= l.endx; i++) {
				ventmap[l.starty][i]++;
			}
		}
	}
	int overlapping = 0;
	for(int i = 0; i < MAX_COORD; i++) {
		for(int j = 0; j < MAX_COORD; j++) {
			if(ventmap[i][j] > 1) {
				overlapping++;
			}
			/*if(ventmap[i][j] == 0) {
				cout << ".";
			} else {
				cout << ventmap[i][j];
			}*/
		}
		cout << endl;
	}

	cout << "Overlapping lines " << overlapping << endl;
}