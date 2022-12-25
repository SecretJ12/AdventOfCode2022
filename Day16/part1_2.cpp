#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct state {
    string pos;
    set<string> opened;
    long released;
    int steps;
};
const static int MAX_STEPS = 30;

int main() {
    ifstream input ("testinput.txt");
    if (input.is_open()) {
        map<string, long> flow;
        map<string, set<string>> paths;
        {
            string line;
            while (getline(input, line)) {
                string_view wLine{line};

                string_view name{wLine.substr(6, 2)};
                size_t pos{wLine.find(';')};
                flow[string{name}] = atol(wLine.substr(23, pos).begin());

                set<string> curPaths;
                while ((pos = wLine.find(',')) != string::npos) {
                    curPaths.insert(string{wLine.substr(pos - 2, 2)});
                    wLine = wLine.substr(pos + 2);
                }
                wLine = wLine.substr(wLine.size() - 2);
                curPaths.insert(string{wLine});
                paths[string{name}] = curPaths;
            }
        }

        queue<state> states;
        states.emplace("AA", set<string>{}, 0, 0);
        map<string, long> bestMov;
        long best{0};
        while (!states.empty()) {
            state s = states.front();
            states.pop();

            // OPEN CURRENT VAULT
            if (!s.opened.contains(s.pos)) {
                state new_s{s};
                ++new_s.steps;
                new_s.released += flow[new_s.pos]*(MAX_STEPS - new_s.steps);
                new_s.opened.insert(new_s.pos);
                best = max(best, new_s.released);
                if (bestMov[s.pos] < new_s.released) {
                    states.push(new_s);
                    bestMov[new_s.pos] = max(bestMov[new_s.pos], new_s.released);
                }
            }
            // ANY DIRECTION
            for (const string& new_pos : paths[s.pos]) {
                state new_s{s};
                new_s.pos = new_pos;
                ++new_s.steps;
                if (new_s.steps < MAX_STEPS && (!bestMov.contains(new_pos) || bestMov[new_pos] < new_s.released)) {
                    states.push(new_s);
                    if (bestMov.contains(new_pos))
                        bestMov[new_pos] = max(bestMov[new_pos], new_s.released);
                    else
                        bestMov[new_pos] = new_s.released;
                }
            }
        }
        cout << best << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
