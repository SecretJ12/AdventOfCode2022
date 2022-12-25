#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;


int main() {
    vector<vector<tuple<char, uint8_t, uint8_t, uint8_t, uint8_t>>> field;
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        while (getline(input, line)) {
            vector<tuple<char, uint8_t, uint8_t, uint8_t, uint8_t>> row;
            for (char c : line) {
                row.emplace_back(c, c, c, c, c);
            }
            field.push_back(row);
        }
    } else {
        cout << "Unable to open file";
    }

    for (size_t x{0}; x < field.size(); ++x) {
        for (size_t y{0}; y < field.size(); ++y) {
            if (x > 0) {
                get<1>(field[x][y]) = max(get<1>(field[x-1][y]), get<1>(field[x][y]));
            }
            if (y > 0) {
                get<4>(field[x][y]) = max(get<4>(field[x][y-1]), get<4>(field[x][y]));
            }
        }
    }
    for (size_t a{0}; a < field.size(); ++a) {
        for (size_t b{0}; b < field.size(); ++b) {
            size_t x = field.size()-a-1;
            size_t y = field.size()-b-1;

            if (x < field.size()-1) {
                get<3>(field[x][y]) = max(get<3>(field[x+1][y]), get<3>(field[x][y]));
            }
            if (y < field.size()-1) {
                get<2>(field[x][y]) = max(get<2>(field[x][y+1]), get<2>(field[x][y]));
            }
        }
    }

    for (size_t x{0}; x < field.size(); ++x) {
        for (size_t y{0}; y < field.size(); ++y) {
            auto& [v, n, e, s, w] = field[x][y];
            cout << v << "(" << n << "," << e << "," << s << "," << w << ") ";
        }
        cout << endl;
    }

    long visible{0};
    for (size_t x{0}; x < field.size(); ++x) {
        for (size_t y{0}; y < field.size(); ++y) {
            bool ok = false;
            // check north
            if (x > 0)
                ok |= get<0>(field[x][y]) > get<1>(field[x-1][y]);
            else
                ok = true;

            // check east
            if (y < field.size()-1)
                ok |= get<0>(field[x][y]) > get<2>(field[x][y+1]);
            else
                ok = true;

            // check south
            if (x < field.size()-1)
                ok |= get<0>(field[x][y]) > get<3>(field[x+1][y]);
            else
                ok = true;

            // check west
            if (y > 0)
                ok |= get<0>(field[x][y]) > get<4>(field[x][y-1]);
            else
                ok = true;

            if (ok) {
                ++visible;

                cout << "x";
            } else
                cout << " ";
        }
        cout << endl;
    }

    cout << "Visible trees: " << visible << endl;

    return 0;
}
