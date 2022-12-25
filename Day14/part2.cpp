#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

using namespace std;

pair<size_t, size_t> parse(string_view v) {
    size_t pos = v.find(',');
    size_t x = static_cast<size_t>(atoll(v.substr(0, pos).begin()));
    size_t y = static_cast<size_t>(atoll(v.substr(pos+1).begin()));
    return make_pair(x, y);
}

void print(vector<vector<bool>> map) {
    size_t minX{1000};
    size_t maxX{0};
    size_t maxY{0};
    for (size_t y{0}; y < map.size(); ++y) {
        for (size_t x{0}; x < map[y].size(); ++x) {
            if (map[y][x]) {
                minX = min(minX, x);
                maxX = max(maxX, x);
                maxY = max(maxY, y);
            }
        }
    }
    for (size_t y{0}; y <= maxY; ++y) {
        for (size_t x{minX}; x <= maxX; ++x) {
            if (map[y][x])
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
}

int main() {
    string line;
    ifstream input ("inputhanna.txt");
    if (input.is_open()) {
        vector<vector<bool>> map;
        vector<bool> row;
        row.resize(1000, false);
        map.resize(200, row);

        size_t maxY;
        while (getline(input, line)) {
            string_view wLine{line};
            optional<pair<size_t, size_t>> lastPos;
            while (!wLine.empty()) {
                size_t pos = wLine.find(" -> ");
                string_view cur;
                if (pos != string::npos) {
                    cur = wLine.substr(0, pos);
                    wLine = wLine.substr(pos+4);
                } else {
                    cur = string_view{wLine};
                    wLine = wLine.substr(0, 0);
                }

                pair<size_t, size_t> curPos{parse(cur)};
                maxY = max(maxY, curPos.second);

                if (lastPos.has_value()) {
                    if (lastPos.value().first != curPos.first) {
                        for (size_t x{min(lastPos.value().first, curPos.first)}; x <= max(lastPos.value().first, curPos.first); ++x) {
                            map[curPos.second][x] = true;
                        }
                    } else {
                        for (size_t y{min(lastPos.value().second, curPos.second)}; y <= max(lastPos.value().second, curPos.second); ++y) {
                            map[y][curPos.first] = true;
                        }
                    }
                }
                lastPos = make_optional(curPos);
            }
        }
        maxY += 2;
        for (size_t x{0}; x < map[maxY].size(); ++x) {
            map[maxY][x] = true;
        }
        print(map);

        long long ctr{0};
        pair<size_t, size_t> pos = make_pair(500, 0);
        while (true) {
            if (!map[pos.second+1][pos.first]) {
                ++pos.second;
            } else if (!map[pos.second+1][pos.first-1]) {
                ++pos.second;
                --pos.first;
            } else if (!map[pos.second+1][pos.first+1]) {
                ++pos.second;
                ++pos.first;
            } else {
                ++ctr;
                map[pos.second][pos.first] = true;
                if (pos.second == 0) {
                    break;
                }

                pos = make_pair(500, 0);
            }
        }
        print(map);
        cout << "I used " << ctr << " units of sand" << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
