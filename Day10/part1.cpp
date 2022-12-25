#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        size_t cycle{1};
        int X{1};
        int sum{0};
        while (getline(input, line)) {
            cout << "Cycle " << cycle << ": " << X << " (" << sum << ") [" << line << "]" << endl;
            if (line.starts_with("noop") && cycle % 40 == 20)
                sum += X * cycle;
            if (line.starts_with("addx")) {
                if (cycle % 40 == 19)
                    sum += X * (cycle+1);
                if (cycle % 40 == 20)
                    sum += X * cycle;
                X += atoi(string_view{line}.substr(5).begin());
                ++cycle;
            }
            ++cycle;
        }
        cout << sum << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
