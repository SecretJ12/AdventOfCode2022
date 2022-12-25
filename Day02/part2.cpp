#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, uint64_t> mapping{{'A', 0}, {'B', 1}, {'C', 2}};
unordered_map<char, uint64_t> strategy{{'X', 2}, {'Y', 0}, {'Z', 1}};
unordered_map<char, uint64_t> win{{'X', 0}, {'Y', 3}, {'Z', 6}};
int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        uint64_t points{0};
        while (getline(input, line)) {
            points += win[line[2]];
            points += (mapping[line[0]] + strategy[line[2]]) % 3 + 1;
        }
        input.close();

        cout << points << '\n';
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
