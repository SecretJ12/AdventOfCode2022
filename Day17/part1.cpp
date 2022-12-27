#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum Material {
    STONE, AIR
};

enum Motion {
    LEFT, RIGHT
};

class Cave {
public:
    Cave(): highest{-1}, cave{} {}

    [[nodiscard]] int getHighest() const {
        return highest;
    }

    Material get(int x, int y) {
        if (x < 0 || y < 0 || y >= width)
            return STONE;
        if (x > highest)
            return AIR;
        return cave.at(static_cast<unsigned long>(x)).at(static_cast<unsigned long>(y));
    }

    bool placeable(vector<vector<Material>>& fig, int x, int y) {
        for (uint dx{0}; dx < fig.size(); ++dx) {
            for (uint dy{0}; dy < fig[dx].size(); ++dy) {
                if (fig[dx][dy] == STONE && get(x - static_cast<int>(dx), y + static_cast<int>(dy)) == STONE)
                    return false;
            }
        }
        return true;
    }

    void place(vector<vector<Material>>& fig, int x, int y) {
        while (x >= static_cast<int>(cave.size()))
            cave.emplace_back(width, AIR);
        for (uint dx{0}; dx < fig.size(); ++dx) {
            for (uint dy{0}; dy < fig[dx].size(); ++dy) {
                if (fig[dx][dy] == STONE) {
                    cave[static_cast<uint>(x) - dx][static_cast<uint>(y) + dy] = STONE;
                    highest = max(highest, x);
                }
            }
        }
    }

    void print() {
        print(cave.size());
    }

    void print(size_t height) {
        auto f =  vector<vector<Material>>();
        print(height, -1, -1, f);
    }

    void print(size_t height, long long cx, long long cy, vector<vector<Material>>& figure) {
        if (cx > static_cast<long long>(cave.size()) - 1)
            for (size_t x{0}; x < static_cast<size_t>(cx) - cave.size() + 1; ++x) {
                cout << "|";
                const auto &line = cave[cave.size() - 1 - x];
                for (size_t y{0}; y < line.size(); ++y) {
                    if (static_cast<long long>(y) >= cy
                        && static_cast<long long>(y)
                           < cy + static_cast<long long>(figure[x].size())) {
                        if (figure[x][y-static_cast<size_t>(y)] == AIR)
                            cout << ".";
                        else
                            cout << '@';
                        continue;
                    } else
                        cout << ".";
                }
                cout << "|" << endl;
            }
        for (size_t x{0}; x < min(cave.size(), height); ++x) {
            cout << "|";
            const auto &line = cave[cave.size() - 1 - x];
            for (size_t y{0}; y < line.size(); ++y) {
                if (highest - static_cast<long long>(x) <= cx
                    && highest - static_cast<long long>(x) > cx - static_cast<long long>(figure.size())
                    && static_cast<long long>(y) >= cy
                    && static_cast<long long>(y)
                       < cy + static_cast<long long>(figure[static_cast<size_t>(cx - getHighest()) + x].size())) {
                    if (figure[x + (static_cast<size_t>(cx - getHighest()))][y-static_cast<size_t>(y)] == AIR)
                        cout << ".";
                    else
                        cout << '@';
                    continue;
                }

                auto m = line[y];
                if (m == AIR)
                    cout << ".";
                else if (m == STONE)
                    cout << "#";
            }
            cout << "|" << endl;
        }
        if (cave.size() > height)
            cout << endl;
        cout << "+";
        for (size_t y{0}; y < static_cast<size_t>(width); ++y) {
            cout << "-";
        }
        cout << "+" << endl;
    }
private:
    const int width = 7;
    int highest;
    vector<vector<Material>> cave;
};

class Jet {
public:
    Jet() = delete;
    Jet(string_view input) : cur{0} {
        for (char c : input) {
            if (c == '<')
                gases.push_back(LEFT);
            else if (c == '>')
                gases.push_back(RIGHT);
            else
                cerr << "Error reading input " << c << endl;
        }
    }

    Motion next()  {
        Motion curM = gases[cur];
        cur = (cur + 1) % gases.size();
        return curM;
    }
private:
    size_t cur;
    vector<Motion> gases;
};

class Figures {
public:
    Figures() : cur{0} {}
    vector<vector<Material>> next() {
        auto curF = figures[cur];
        cur = (cur + 1) % figures.size();
        return curF;
    }
private:
    size_t cur;
    const vector<vector<vector<Material>>> figures{
            vector<vector<Material>>{
                    vector<Material>{
                            STONE, STONE, STONE, STONE
                    }
            },
            vector<vector<Material>>{
                    vector<Material>{
                            AIR, STONE, AIR
                    },
                    vector<Material>{
                            STONE, STONE, STONE
                    },
                    vector<Material>{
                            AIR, STONE, AIR
                    }
            },
            vector<vector<Material>>{
                    vector<Material>{
                            AIR, AIR, STONE
                    },
                    vector<Material>{
                            AIR, AIR, STONE
                    },
                    vector<Material>{
                            STONE, STONE, STONE
                    }
            },
            vector<vector<Material>>{
                    vector<Material>{
                            STONE
                    },
                    vector<Material>{
                            STONE
                    },
                    vector<Material>{
                            STONE
                    },
                    vector<Material>{
                            STONE
                    }
            },
            vector<vector<Material>>{
                    vector<Material>{
                            STONE, STONE
                    },
                    vector<Material>{
                            STONE, STONE
                    }
            }
    };
};

int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        getline(input, line);
        Cave cave{};
        Jet jet{line};
        Figures figures{};
        cout << "Constructed cave and figures and read in jet" << endl;

        for (int i{0}; i < 1; ++i) {
            auto figure = figures.next();

            int x{cave.getHighest() + 3 + static_cast<int>(figure.size())};
            int y{2};

            while (true) {
                Motion m = jet.next();
                if (m == RIGHT) {
                    ++y;
                    if (!cave.placeable(figure, x, y))
                        --y;
                } else {
                    --y;
                    if (!cave.placeable(figure, x, y))
                        ++y;
                }

                --x;
                if (!cave.placeable(figure, x, y)) {
                    ++x;
                    cave.place(figure, x, y);
                    break;
                }
            }
            cout << "Placed figure " << i+1 << endl;
            //cave.print();
        }
        cave.print(30);
        cout << cave.getHighest()+1 << endl;
    } else {
        cout << "Unable to open file";
    }
    return 0;
}
