#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Test for happy day scenario where there is always at least one arrangement for the row
uint32_t calculateArrangements(string line, vector<uint32_t> row)
{
    uint32_t arrangements = 0;
    line.erase(line.find_last_not_of('.') + 1);
    line.erase(0, line.find_first_not_of('.'));
    cout << "Calculating arrangements for row " << line << endl;
    cout << "Patterns ";
    for (auto i : row) {
        cout << i << " ";
    }
    cout << endl;

    // Trim first and last dots


    uint32_t minimum_size = row.size() - 1;
    for (auto i : row) {
        minimum_size += i;
    }

    // Only one possibility
    if (minimum_size == line.size()) {
        cout << "Trivial case, only one arrangement" << endl;
        return 1;
    }

    uint32_t first_element = row.front();
    // First of the line is always a ? or #, # is trivial and has only 1 arrangement
    if (line[0] == '#') {
        cout << "# Found from beginning, recursion" << endl;
        string newline = line.substr(first_element);
        arrangements = 1;
        vector<uint32_t> newrow;
        for (int i = 1; i < row.size(); i++) {
            newrow.push_back(row.at(i));
        }
        arrangements *= calculateArrangements(newline, newrow);
    } else {
        // While the first one is ?, test if the ### can start from it
        cout << "? Found from beginning, recursion" << endl;
        for (int i = 0; i < line.size() - minimum_size; i++) {
            bool end = false;
            bool legal = true;
            bool substitute_next = false;
            bool end_of_line = false;
            // If first of the group is #, this is the last position we check
            if (line[i] == '#') {
                end = true;
            }

            // Check if the pattern is legal
            for (int j = i; j < i + first_element; j++) {
                if (line[j] == '.') {
                    cout << "Doesn't fit, illegal pattern" << endl;
                    legal = false;
                }
            }

            if (i + first_element == line.size()) {
                cout << "Last of the line" << endl;
                end_of_line = true;
            } else if (line[i+first_element] == '#') {
                legal = false;
            } else if (line[i+first_element] == '?') {
                substitute_next = true;
            }
            // Check the next mark after the pattern
            if (legal == true) {
                arrangements++;
                if (end_of_line) break;
                string newline = line.substr(i+first_element);
                if (substitute_next) {
                    newline[0] = '.';
                }
                vector<uint32_t> newrow;
                for (int k = 1; k < row.size(); k++) {
                    newrow.push_back(row.at(k));
                }
                arrangements *= calculateArrangements(newline, newrow);
            }

            if (end) {
                break;
            }
        }
    }

    cout << "Number of arrangements " << arrangements << endl;
    return arrangements;
}

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    uint32_t arrangementSum = 0;

	while(getline(infile, buffer)) {
        stringstream ss(buffer);
        vector<uint32_t> row;
        string line;
        ss >> line;
        string element;
        while(getline(ss, element, ','))
        {
            uint32_t elem;
            elem = stoi(element);
            row.push_back(elem);
        }
        arrangementSum += calculateArrangements(line, row);
        cout << endl << "Arrangements total " << arrangementSum << endl;
	}

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Sum of arrangements " << arrangementSum << " time taken " << duration.count() << " us" << endl;
}
