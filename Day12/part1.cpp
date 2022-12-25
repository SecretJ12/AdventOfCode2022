#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

int height(char c) {
    if (c == 'S')
        return 1;
    if (c == 'E')
        return 26;
    return c - 'a' + 1;
}

int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        vector<vector<pair<char, ulong>>> map;
        queue<pair<size_t, size_t>> next;

        for (size_t x{0}; getline(input, line); ++x) {
            vector<pair<char, ulong>> row;
            for (size_t y{0}; y < line.size(); ++y) {
                if (line[y] == 'S') {
                    next.emplace(x, y);
                    row.emplace_back(line[y], 0);
                } else {
                    row.emplace_back(line[y], ULONG_MAX);
                }
            }
            map.push_back(row);
        }

        while (!next.empty()) {

            auto& [x, y] = next.front();
            int curHeight{height(map[x][y].first)};
            ulong curPath{map[x][y].second};

            if (map[x][y].first == 'E') {
                cout << "Found path with " << curPath << " steps!" << endl;
                return 0;
            }

            if (x > 0) {
                if (height(map[x-1][y].first) <= curHeight+1 && map[x-1][y].second > curPath+1) {
                    map[x-1][y].second = curPath + 1;
                    next.emplace(x-1, y);
                }
            }
            if (y > 0) {
                if (height(map[x][y-1].first) <= curHeight+1 && map[x][y-1].second > curPath+1) {
                    map[x][y-1].second = curPath + 1;
                    next.emplace(x, y-1);
                }
            }
            if (x < map.size()-1) {
                if (height(map[x+1][y].first) <= curHeight+1 && map[x+1][y].second > curPath+1) {
                    map[x+1][y].second = curPath + 1;
                    next.emplace(x+1, y);
                }
            }
            if (y < map[0].size()-1) {
                if (height(map[x][y+1].first) <= curHeight+1 && map[x][y+1].second > curPath+1) {
                    map[x][y+1].second = curPath + 1;
                    next.emplace(x, y+1);
                }
            }

            next.pop();

            if (false)
                for (auto row : map) {
                    for (auto [c, p] : row) {
                        if (p == ULONG_MAX) {
                            cout << "##";
                        } else {
                            if (p < 10) {
                                cout << "0";
                            }
                            cout << p;
                        }
                        cout << "(" << c << ") ";
                    }
                    cout << endl;
                }
        }
        cout << "No path found!";
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
