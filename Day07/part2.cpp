#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <tuple>
#include <climits>

using namespace std;

long calculateStorage(ifstream& input) {
    string line;
    getline(input, line);

    long size{0};
    while (getline(input, line)) {
        string_view curLine{line};
        string_view first{curLine.substr(0, curLine.find(' '))};
        string_view second{curLine.substr(curLine.find(' ')+1)};

        if (first == "dir") {
            continue;
        }
        if (first == "$") {
            if (second == "cd ..") {
                break;
            } else {
                long sizeSub = calculateStorage(input);
                size += sizeSub;
                continue;
            }
        }
        size += atol(first.begin());
    }
    return size;
}

std::pair<long, long> find(ifstream& input, long storageMissing) {
    string line;
    getline(input, line);

    long size{0};
    long n{LONG_MAX};
    while (getline(input, line)) {
        string_view curLine{line};
        string_view first{curLine.substr(0, curLine.find(' '))};
        string_view second{curLine.substr(curLine.find(' ')+1)};

        if (first == "dir") {
            continue;
        }
        if (first == "$") {
            if (second == "cd ..") {
                break;
            } else {
                auto p = find(input, storageMissing);
                auto& [sizeSub, nSub] = p;
                size += sizeSub;
                n = min(n, nSub);
                continue;
            }
        }
        size += atol(first.begin());
    }
    if (size >= storageMissing)
        n = min(n, size);
    return make_pair(size, n);
}

int main() {
    static constexpr string inputFile = "input.txt";

    string line;
    ifstream input{inputFile};
    long storageMissing;
    if (input.is_open()) {
        getline(input, line);
        long size = calculateStorage(input);
        cout << "Currently occupied " << size << endl;
        cout << "Currently free " << 70000000 - size << endl;
        storageMissing = 30000000 - (70000000 - size);
        cout << "Missing storage " << storageMissing << endl;
    } else {
        cout << "Unable to open file" << endl;
    }

    input = ifstream{inputFile};
    if (input.is_open()) {
        getline(input, line);
        auto p = find(input, storageMissing);
        auto& [size, n] = p;
        cout << "Smallest directory " << n << endl;
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}
