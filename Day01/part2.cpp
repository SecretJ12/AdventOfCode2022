#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        uint64_t first{0};
        uint64_t second{0};
        uint64_t third{0};
        uint64_t current{0};
        while (getline(input, line)) {
            if (line.empty()) {
                if (current > third)
                    third = current;
                if (third > second)
                    swap(second, third);
                if (second > first)
                    swap(first, second);
                current = 0;
            } else {
                current += stoull(line);
            }
        }
        if (current > third)
            third = current;
        if (third > second)
            swap(second, third);
        if (second > first)
            swap(first, second);
        input.close();

        cout << (first+second+third) << '\n';
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
