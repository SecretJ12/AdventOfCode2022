#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        uint64_t largest{0};
        uint64_t current{0};
        while (getline(input, line)) {
            if (line.empty()) {
                if (current > largest)
                    largest = current;
                current = 0;
            } else {
                current += stoull(line);
            }
        }
        if (current > largest)
            largest = current;
        input.close();

        cout << largest << '\n';
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
