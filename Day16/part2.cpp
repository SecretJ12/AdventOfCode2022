#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <memory>

using namespace std;

struct state {
    string pos1;
    string pos2;
    set<string> opened;
    long released;

    bool operator <(const state &s) const {
        return released < s.released;
    }
};
const static int MAX_STEPS = 26;

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

        auto next_states = make_shared<priority_queue<state>>();
        auto states = make_shared<priority_queue<state>>();
        states->push(state{"AA", "AA", set<string>{}, 0});
        long best{0};
        for (int step{1}; step < MAX_STEPS; ++step) {
            cout << step << " ";
            int ctr{0};
            while (!states->empty() && (++ctr) < 100000) {
                state s = states->top();
                states->pop();
                // cout << " " << s.released;

                // OPEN CURRENT VAULT
                if (!s.opened.contains(s.pos1)) {
                    state new_s{s};
                    new_s.released += flow[new_s.pos1]*(MAX_STEPS - step);
                    new_s.opened.insert(new_s.pos1);

                    // OPEN CURRENT VAULT
                    if (!new_s.opened.contains(s.pos2)) {
                        state new_s2{new_s};
                        new_s2.released += flow[new_s2.pos2] * (MAX_STEPS - step);
                        new_s2.opened.insert(new_s2.pos2);
                        best = max(best, new_s2.released);
                        next_states->push(new_s2);
                    }
                    // ANY DIRECTION
                    for (const string& new_pos : paths[s.pos2]) {
                        state new_s2{new_s};
                        new_s2.pos2 = new_pos;
                        next_states->push(new_s2);
                    }
                }
                // ANY DIRECTION
                for (const string& new_pos : paths[s.pos1]) {
                    state new_s{s};
                    new_s.pos1 = new_pos;

                    // OPEN CURRENT VAULT
                    if (!new_s.opened.contains(s.pos2)) {
                        state new_s2{new_s};
                        new_s2.released += flow[new_s2.pos2] * (MAX_STEPS - step);
                        new_s2.opened.insert(new_s2.pos2);
                        best = max(best, new_s2.released);
                        next_states->push(new_s2);
                    }
                    // ANY DIRECTION
                    for (const string& new_pos2 : paths[s.pos2]) {
                        state new_s2{new_s};
                        new_s2.pos2 = new_pos2;
                        next_states->push(new_s2);
                    }
                }
            }
            states = shared_ptr{next_states};
            next_states = make_shared<priority_queue<state>>();
            cout << best;
            cout << endl;
        }
        cout << endl;
        cout << best << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
