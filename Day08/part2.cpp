#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int main() {
    vector<vector<char>> field;
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        while (getline(input, line)) {
            vector<char> row;
            for (char c : line) {
                row.emplace_back(c);
            }
            field.push_back(row);
        }
    } else {
        cout << "Unable to open file";
    }

    long bestView{0};
    for (size_t x{1}; x < field.size()-1; ++x) {
        for (size_t y{1}; y < field.size()-1; ++y) {
            long view{1};
            // north
            for (size_t i{1}; i <= x; ++i) {
                if (field[x][y] <= field[x-i][y] || i == x) {
                    view *= static_cast<long>(i);
                    break;
                }
            }
            // east
            for (size_t i{1}; i < field.size()-y; ++i) {
                if (field[x][y] <= field[x][y+i] || i == field.size()-y-1) {
                    view *= static_cast<long>(i);
                    break;
                }
            }
            // south
            for (size_t i{1}; i < field.size()-x; ++i) {
                if (field[x][y] <= field[x+i][y] || i == field.size()-x-1) {
                    view *= static_cast<long>(i);
                    break;
                }
            }
            // west
            for (size_t i{1}; i <= y; ++i) {
                if (field[x][y] <= field[x][y-i] || i == y) {
                    view *= static_cast<long>(i);
                    break;
                }
            }
            bestView = max(bestView, view);
        }
    }

    cout << "Best view: " << bestView << endl;

    return 0;
}
