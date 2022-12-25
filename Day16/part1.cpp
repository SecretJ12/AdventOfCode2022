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

    bool operator <(const state &s) const {
        return released < s.released;
    }
};
const static int MAX_STEPS = 30;

int main() {
    ifstream input ("input.txt");
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

        priority_queue<state> next_states;
        priority_queue<state> states;
        states.push(state{"AA", set<string>{}, 0});
        long best{0};
        for (int step{1}; step < MAX_STEPS; ++step) {
            int ctr{0};
            cout << step;
            while (!states.empty() && (++ctr) < 10000) {
                state s = states.top();
                states.pop();
                // cout << " " << s.pos << "(" << s.released << ")";

                // OPEN CURRENT VAULT
                if (!s.opened.contains(s.pos)) {
                    state new_s{s};
                    new_s.released += flow[new_s.pos]*(MAX_STEPS - step);
                    new_s.opened.insert(new_s.pos);
                    best = max(best, new_s.released);
                    next_states.push(new_s);
                }
                // ANY DIRECTION
                for (const string& new_pos : paths[s.pos]) {
                    state new_s{s};
                    new_s.pos = new_pos;
                    next_states.push(new_s);
                }
            }
            states = next_states;
            next_states = priority_queue<state>{};
            cout << endl;
        }
        cout << best << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
