#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <stack>

using namespace std;


int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        vector<stack<char>> stacks;
        uint64_t nStacks{};
        while (getline(input, line)) {
            nStacks = max((line.length()+1)/4, nStacks);
            stacks.resize(nStacks);
            if (line[1] == '1')
                break;
            for (uint64_t i{0}; i < nStacks; ++i) {
                char c{line[1+4*i]};
                if (c == ' ')
                    continue;
                cout << i << c;
                stacks[i].push(c);
            }
            cout << '\n';
        }

        getline(input, line);
        for (uint64_t i{0}; i < nStacks; ++i) {
            stack<char> bufStack;
            while (!stacks[i].empty()) {
                bufStack.push(stacks[i].top());
                cout << stacks[i].top();
                stacks[i].pop();
            }
            stacks[i] = bufStack;
            cout << '\n';
        }

        while (getline(input, line)) {
            uint64_t firstSpace = line.find(' ');
            uint64_t secondSpace = line.find(' ', firstSpace+1);
            uint64_t thirdSpace = line.find(' ', secondSpace+1);
            uint64_t fourthSpace = line.find(' ', thirdSpace+1);
            uint64_t fifthSpace = line.find(' ', fourthSpace+1);

            size_t count{static_cast<size_t>(atoll(string_view(line).substr(firstSpace+1, secondSpace).begin()))};
            size_t from{static_cast<size_t>(atoll(string_view(line).substr(thirdSpace+1, fourthSpace).begin()))-1};
            size_t to{static_cast<size_t>(atoll(string_view(line).substr(fifthSpace+1, line.length()).begin()))-1};

            for (size_t i{0}; i < count; ++i) {
                stacks[to].push(stacks[from].top());
                stacks[from].pop();
            }
        }

        input.close();

        for (size_t i{0}; i < nStacks; ++i) {
            cout << stacks[i].top();
        }
        cout << '\n';
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
