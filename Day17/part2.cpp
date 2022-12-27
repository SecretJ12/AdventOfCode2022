#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

long long TOTAL = 1000000000000;

enum Material {
    STONE, AIR
};

enum Motion {
    LEFT, RIGHT
};

class Cave {
public:
    Cave() : highest{-1}, cave{} {}

    [[nodiscard]] long long getHighest() const {
        return highest;
    }

    Material get(long long x, long long y) {
        if (x < 0 || y < 0 || y >= width)
            return STONE;
        if (x > highest)
            return AIR;
        return cave.at(static_cast<unsigned long>(x)).at(static_cast<unsigned long>(y));
    }

    bool placeable(vector<vector<Material>> &fig, long long x, long long y) {
        for (uint dx{0}; dx < fig.size(); ++dx) {
            for (uint dy{0}; dy < fig[dx].size(); ++dy) {
                if (fig[dx][dy] == STONE && get(x - static_cast<long long>(dx), y + static_cast<long long>(dy)) == STONE)
                    return false;
            }
        }
        return true;
    }

    void place(vector<vector<Material>> &fig, long long x, long long y) {
        while (x >= static_cast<long long>(cave.size()))
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
    long long highest;
    vector<vector<Material>> cave;
};

class Jet {
public:
    Jet() = delete;

    Jet(string_view input) : cur{0} {
        for (char c: input) {
            if (c == '<')
                gases.push_back(LEFT);
            else if (c == '>')
                gases.push_back(RIGHT);
            else
                cerr << "Error reading input " << c << endl;
        }
    }

    Motion next() {
        Motion curM = gases[cur];
        // cout << cur << " / " << gases.size() << endl;
        cur = (cur + 1) % gases.size();
        return curM;
    }

    bool isFirst() const {
        return cur == 0;
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

    bool isFirst() const {
        return cur == 0;
    }

    void undo() {
        --cur;
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
    ifstream input("input.txt");
    if (input.is_open()) {
        getline(input, line);
        Cave cave{};
        Jet jet{line};
        Figures figures{};
        cout << "Constructed cave and figures and read in jet" << endl;

        // go through jet iteration once
        long long fi;
        long long fx;
        long long fy;
        for (long long i{0}; i < TOTAL; ++i) {
            auto figure = figures.next();

            long long x{cave.getHighest() + 3 + static_cast<int>(figure.size())};
            long long y{2};

            while (true) {
                if (jet.isFirst() && i != 0) {
                    fi = i;
                    fx = x;
                    fy = y;
                    cave.print(20, x, y, figure);
                    goto secondIteration;
                }
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
        }
        secondIteration:
        cout << "Completed first iteration" << endl;
        long long firstHeight{cave.getHighest()};
        // do second iteration to get difference
        long long si;
        long long sx;
        long long sy;
        figures.undo();
        for (long long i{fi}; i < TOTAL; ++i) {
            auto figure = figures.next();

            long long x{cave.getHighest() + 3 + static_cast<long long>(figure.size())};
            long long y{2};
            if (i == fi) {
                x = fx;
                y = fy;
            }

            while (true) {
                if (jet.isFirst() && i != fi) {
                    si = i;
                    sx = x;
                    sy = y;
                    cave.print(20, x, y, figure);
                    goto thirdIteration;
                }
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
        }
        thirdIteration:
        cout << "Completed second iteration" << endl;
        long long secondHeight{cave.getHighest()};
        cout << "Figure diff: " << si - fi << endl;
        cout << "Height diff: " << cave.getHighest() - firstHeight << endl;
        // Complete rest of iterations
        figures.undo();
        long long startAt = fi + ((TOTAL - fi) / (si - fi) * (si - fi));
        for (long long i{startAt}; i < TOTAL; ++i) {
            auto figure = figures.next();

            long long x{cave.getHighest() + 3 + static_cast<long long>(figure.size())};
            long long y{2};
            if (i == startAt) {
                x = sx;
                y = sy;
                //cave.print(20, x, y, figure);
            }

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
        }
        long long sol = cave.getHighest() + (secondHeight - firstHeight) * ((TOTAL - si) / (si - fi));
        // + 1 cause array start at 0...
        cout << "Height: " << sol + 1 << endl;
    } else {
        cout << "Unable to open file";
    }
    return 0;
}