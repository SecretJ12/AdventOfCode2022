#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        int cycle{1};
        int X{1};
        while (getline(input, line)) {
            if (abs(X-((cycle-1)%40)) <= 1)
                cout << "#" << flush;
            else
                cout << "." << flush;
            if (line.starts_with("addx")) {
                if (cycle % 40 == 0)
                    cout << endl;
                ++cycle;
                if (abs(X-((cycle-1)%40)) <= 1)
                    cout << "#" << flush;
                else
                    cout << "." << flush;
                X += atoi(string_view{line}.substr(5).begin());
            }
            if (cycle % 40 == 0)
                cout << endl;
            ++cycle;
        }
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
