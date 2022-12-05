#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;
/*
[T]     [D]         [L]            
[R]     [S] [G]     [P]         [H]
[G]     [H] [W]     [R] [L]     [P]
[W]     [G] [F] [H] [S] [M]     [L]
[Q]     [V] [B] [J] [H] [N] [R] [N]
[M] [R] [R] [P] [M] [T] [H] [Q] [C]
[F] [F] [Z] [H] [S] [Z] [T] [D] [S]
[P] [H] [P] [Q] [P] [M] [P] [F] [D]
 1   2   3   4   5   6   7   8   9 
*/
int main()
{
	ifstream infile("input.txt");
	vector<char> contents[9]{{'p', 'f', 'm', 'q', 'w', 'g', 'r', 't'},
				 {'h', 'f', 'r'},
				 {'p', 'z', 'r', 'v', 'g', 'h', 's', 'd'},
				 {'q', 'h', 'p', 'b', 'f', 'w', 'g'},
				 {'p', 's', 'm', 'j', 'h'},
				 {'m', 'z', 't', 'h', 's', 'r', 'p', 'l'},
				 {'p', 't', 'h', 'n', 'm', 'l'},
				 {'f', 'd', 'q', 'r'},
				 {'d', 's', 'c', 'n', 'l', 'p', 'h'}};
	stack<char, vector<char>> stacks[9];

	for (int i = 0; i < 9; i++) {
		for (auto c : contents[i]) {
			stacks[i].push(c);
		}
	}

	string buffer;

	while (getline(infile, buffer)) {
		stringstream ss(buffer);
		int i,j,k;
		string temp;

		ss >> temp >> i >> temp >> j >> temp >> k;

		for (int counter = 0; counter < i; counter++) {
			stacks[k-1].push(stacks[j-1].top());
			stacks[j-1].pop();
		}
	}

	cout << "Tops of the stack:" << endl;
	for (int i = 0; i < 9; i++) {
		cout << stacks[i].top();
	}

	cout << endl;
}
