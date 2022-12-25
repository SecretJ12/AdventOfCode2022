#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

uint64_t priority(char c) {
    auto value = static_cast<uint64_t>(c);
    if (value >= static_cast<uint64_t>('a'))
        return static_cast<uint64_t>(c) - static_cast<uint64_t>('a') + 1;
    else
        return static_cast<uint64_t>(c) - static_cast<uint64_t>('A') + 27;
}

int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        uint64_t priorities{0};
        while (getline(input, line)) {
            unordered_set<char> first;
            for (size_t i{0}; i < line.size()/2; ++i) {
                first.insert(line[i]);
            }
            for (size_t i{line.size()/2}; i < line.size(); ++i) {
                char c = line[i];
                if (first.contains(c)) {
                    priorities += priority(c);
                    first.erase(c);
                }
            }
        }
        input.close();

        cout << priorities << '\n';
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
