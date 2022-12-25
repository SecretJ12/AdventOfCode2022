#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, uint64_t> mapping{{'A', 0}, {'B', 1}, {'C', 2}, {'X', 0}, {'Y', 1}, {'Z', 2}};
unordered_map<char, uint64_t> worth{{'X', 1}, {'Y', 2}, {'Z', 3}};
int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        uint64_t points{0};
        while (getline(input, line)) {
            points += worth[line[2]];
            uint64_t opp{mapping[line[0]]};
            uint64_t my{mapping[line[2]]};
            if (my == opp)
                points += 3;
            else if (my == (opp + 1) % 3)
                points += 6;
        }
        input.close();

        cout << points << '\n';
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
