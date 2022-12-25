#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <set>
#include <vector>

using namespace std;


int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        set<tuple<int, int>> visited;
        vector<pair<int, int>> snake;
        snake.resize(10);
        visited.insert(snake[9]);
        cout << visited.size() << endl;
        while (getline(input, line)) {
            cout << line << endl;
            char c = line[0];
            long n = atol(string_view{line}.substr(2).begin());

            for (long i{0}; i < n; ++i) {
                switch (c) {
                    case 'U': snake[0].first = snake[0].first+1; break;
                    case 'R': snake[0].second = snake[0].second+1; break;
                    case 'D': snake[0].first = snake[0].first-1; break;
                    case 'L': snake[0].second = snake[0].second-1; break;
                    default: cout << "Invalid character (" << c << ")" << endl; exit(1);
                }
                for (size_t j{0}; j < 9; ++j) {
                    pair<int, int> posH = snake[j];
                    pair<int, int> posT = snake[j+1];
                    if (posH.first == posT.first) {
                        if (posH.second > posT.second + 1)
                            ++posT.second;
                        else if (posH.second < posT.second - 1)
                            --posT.second;
                    } else if (posH.second == posT.second) {
                        if (posH.first > posT.first + 1)
                            ++posT.first;
                        else if (posH.first < posT.first - 1)
                            --posT.first;
                    } else if (abs(posH.first - posT.first) + abs(posH.second - posT.second) > 2) {
                        if (posH.first > posT.first) {
                            if (posH.second > posT.second) {
                                ++posT.first;
                                ++posT.second;
                            } else {
                                ++posT.first;
                                --posT.second;
                            }
                        } else {
                            --posT.first;
                            if (posH.second > posT.second)
                                ++posT.second;
                            else
                                --posT.second;
                        }
                    }
                    snake[j] = posH;
                    snake[j+1] = posT;
                }
                cout << snake[0].first << "_" << snake[0].second
                    << " " << snake[1].first << "_" << snake[1].second
                    << " " << snake[2].first << "_" << snake[2].second
                    << " " << snake[3].first << "_" << snake[3].second
                    << " " << snake[4].first << "_" << snake[4].second
                    << " " << snake[5].first << "_" << snake[5].second
                    << " " << snake[6].first << "_" << snake[6].second
                    << " " << snake[7].first << "_" << snake[7].second
                    << " " << snake[8].first << "_" << snake[8].second
                    << " " << snake[9].first << "_" << snake[9].second
                    << endl;
                visited.insert(snake[9]);
            }
        }
        cout << "Totally visited " << visited.size() << " places" << endl;
    } else {
        cout << "Unable to open file";
    }
    return 0;
}
