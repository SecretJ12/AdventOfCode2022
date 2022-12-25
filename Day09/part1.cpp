#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <set>

using namespace std;


int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        set<tuple<int, int>> visited;
        pair<int, int> posH;
        pair<int, int> posT;
        visited.insert(posT);
        cout << visited.size() << endl;
        cout << posH.first << "," << posH.second << " " << posT.first << "," << posT.second << endl;
        while (getline(input, line)) {
            cout << line << endl;
            char c = line[0];
            long n = atol(string_view{line}.substr(2).begin());

            for (long i{0}; i < n; ++i) {
                switch (c) {
                    case 'U': posH.first = posH.first+1; break;
                    case 'R': posH.second = posH.second+1; break;
                    case 'D': posH.first = posH.first-1; break;
                    case 'L': posH.second = posH.second-1; break;
                    default: cout << "Invalid character (" << c << ")" << endl; exit(1);
                }
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
                cout << posH.first << "," << posH.second << " " << posT.first << "," << posT.second << endl;
                visited.insert(posT);
            }
        }
        cout << "Totally visited " << visited.size() << " places" << endl;
    } else {
        cout << "Unable to open file";
    }
    return 0;
}
