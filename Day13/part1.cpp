#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <tuple>

using namespace std;

pair<bool, size_t> findSeparator(string_view s) {
    int level{0};
    for (size_t i{0}; i < s.size(); ++i) {
        if (s[i] == ',' && level == 0)
            return make_pair(true, i);
        if (s[i] == '[')
            ++level;
        else if (s[i] == ']')
            --level;
    }
    return make_pair(false, s.size());
}

int compare(string_view first, string_view second) {
    while (!first.empty() && !second.empty()) {
        auto [exFirst, sepFirst] = findSeparator(first);
        auto [exSecond, sepSecond] = findSeparator(second);

        string_view valFirst = first.substr(0, sepFirst);
        string_view valSecond = second.substr(0, sepSecond);
        if (exFirst)
            first = first.substr(sepFirst+1);
        else
            first = first.substr(0, 0);
        if (exSecond)
            second = second.substr(sepSecond+1);
        else
            second = second.substr(0, 0);

        int com;
        if (valFirst.starts_with('[') && valSecond.starts_with('[')) {
            valFirst = valFirst.substr(1, valFirst.size() - 2);
            valSecond = valSecond.substr(1, valSecond.size() - 2);
            com = compare(valFirst, valSecond);
        } else if (valFirst.starts_with('[')) {
            valFirst = valFirst.substr(1, valFirst.size() - 2);
            com = compare(valFirst, valSecond);
        } else if (valSecond.starts_with('[')) {
            valSecond = valSecond.substr(1, valSecond.size() - 2);
            com = compare(valFirst, valSecond);
        } else {
            long numFirst = atol(valFirst.begin());
            long numSecond = atol(valSecond.begin());
            if (numFirst < numSecond)
                com = -1;
            else if (numFirst == numSecond)
                com = 0;
            else
                com = 1;
        }
        if (com != 0)
            return com;
    }

    if (first.empty() && second.empty())
        return 0;
    if (first.empty())
        return -1;
    return 1;
}

int main() {
    ifstream input ("input.txt");
    if (input.is_open()) {
        ulong sum{0};
        ulong i{1};
        string firstLine;
        string secondLine;
        string emptyLine;
        while (getline(input, firstLine)) {
            string_view first{firstLine};
            getline(input, secondLine);
            string_view second{secondLine};

            first = first.substr(1, first.size()-2);
            second = second.substr(1, second.size()-2);
            if (compare(first, second) < 0) {
                sum += i;
                cout << i << " is correct" << endl;
            } else
                cout << i << " is wrong" << endl;

            getline(input, firstLine);
            ++i;
        }

        cout << "Sum of indices " << sum << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
