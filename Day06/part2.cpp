#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>

using namespace std;


int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        int N{14};
        queue<char> last;
        map<char, int> contained;
        int pos;
        while (getline(input, line)) {
            for (size_t i{0}; i < static_cast<size_t>(N); ++i) {
                char a = line[i];
                last.push(a);
                if (contained.contains(a))
                    ++contained[a];
                else
                    contained[a] = 1;
            }
            if (contained.size() >= static_cast<size_t>(N)) {
                pos = N;
                break;
            }
            for (size_t i{static_cast<size_t>(N)}; i < line.length(); ++i) {
                char c = line[i];

                char a = last.front();
                last.pop();
                if (contained[a] > 1)
                    --contained[a];
                else
                    contained.erase(a);

                if (contained.contains(c))
                    ++contained[c];
                else
                    contained[c] = 1;
                last.push(c);
                if (contained.size() >= static_cast<size_t>(N)) {
                    pos = static_cast<int>(i + 1);
                    break;
                }
            }
            cout << pos << '\n';
        }
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
