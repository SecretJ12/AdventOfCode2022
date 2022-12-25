#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <tuple>

using namespace std;

std::pair<long, long> find(ifstream& input) {
    string line;
    getline(input, line);

    long size{0};
    long n{0};
    while (getline(input, line)) {
        string_view curLine{line};
        string_view first{curLine.substr(0, curLine.find(' '))};
        string_view second{curLine.substr(curLine.find(' ')+1)};

        if (first == "dir")
            continue;
        if (first == "$") {
            if (second == "cd ..") {
                break;
            } else {
                auto p = find(input);
                auto& [sizeSub, nSub] = p;
                size += sizeSub;
                n += nSub;
            }
        }
        size += atol(first.begin());
    }
    if (size <= 100000)
        n += size;
    return make_pair(size, n);
}

int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        getline(input, line);
        auto p = find(input);
        auto& [size, n] = p;
        cout << n << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
