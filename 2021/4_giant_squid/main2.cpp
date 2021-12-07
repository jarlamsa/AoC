#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct bingo_board{
	int numbers[5][5] = {0};
	bool check[5][5] = {0};
	bool bingoed = false;
};

bool check_bingo(struct bingo_board& board) {
	bool found = false;
	//Horizontal
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(board.check[i][j] == 0) {
				break;
			}
			if(j==4) {
				found = true;
				return found;
			}
		}
	}
	//Vertical
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(board.check[j][i] == 0) {
				break;
			}
			if(j==4) {
				found = true;
				return found;
			}
		}
	}
	return found;
}

void set_number(int number, struct bingo_board& board) {
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(board.numbers[i][j] == number) {
				board.check[i][j] = 1;
			}
		}
	}
}

int calc_board_value(struct bingo_board& board) {
	int sum = 0;
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(board.check[i][j] == 0) {
				sum += board.numbers[i][j];
			}
		}
	}
	return sum;
}

int main() {

	vector<bingo_board> boards;
	vector<int> bingonumbers;

	ifstream infile("input.txt");
	//First line contains all the numbers
	string line;
	getline(infile, line);
	stringstream numbers(line);
	while(numbers.good()) {
		string substr;
		getline(numbers, substr, ',');
		bingonumbers.push_back(stoi(substr));
	}

	while(infile.good()) {
		struct bingo_board bboard;
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				infile >> bboard.numbers[i][j];
			}
		}
		boards.push_back(bboard);
	}
	int bingos = 1;
	for(auto n : bingonumbers) {
		cout << "Number " << n << endl;
		int i = 0;
		for(auto it = boards.begin(); it != boards.end(); it++) {
			i++;
			set_number(n, *it);
			if((*it).bingoed == true)
				continue;
			if(check_bingo(*it)){
				cout << "Bingo found " << bingos << endl;
				(*it).bingoed = true;
				cout << "Board value " << calc_board_value(*it) * n << endl;
			}
		}
	}
	return 0;
}