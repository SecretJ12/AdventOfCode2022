#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <functional>

using namespace std;

struct monkey {
    queue<int> inv;
    function<int(int)> fun;
    int test;
    size_t trueTo;
    size_t falseTo;

    int inspected;
};

int main() {
    string line;
    ifstream input ("input.txt");
    vector<monkey> monkeys;
    if (input.is_open()) {
        while (getline(input, line)) {
            monkey mon;

            // inventory
            getline(input, line);
            string_view wrapped{line};
            string_view numbers{wrapped.substr(18)};
            while (numbers.find(',') != string::npos) {
                string_view number{numbers.substr(0, numbers.find(','))};
                mon.inv.emplace(atoi(number.begin()));
                numbers = numbers.substr(numbers.find(' ')+1);
            }
            string_view number{numbers.substr(0, numbers.find(','))};
            mon.inv.emplace(atoi(number.begin()));

            // operation
            getline(input, line);
            wrapped = string_view{line};
            if (wrapped.substr(25) == "old") {
                if (wrapped[23] == '*')
                    mon.fun = [](int a){ return a * a; };
                else if (wrapped[23] == '+')
                    mon.fun = [](int a){ return a + a; };
                else
                    cout << "Error" << endl;
            } else {
                int val = atoi(wrapped.substr(25).begin());
                if (wrapped[23] == '*')
                    mon.fun = [val](int a){ return a * val; };
                else if (wrapped[23] == '+')
                    mon.fun = [val](int a){ return a + val; };
                else
                    cout << "Error" << endl;
            }

            // test
            getline(input, line);
            wrapped = string_view{line};
            mon.test = atoi(wrapped.substr(21).begin());

            // true
            getline(input, line);
            wrapped = string_view{line};
            mon.trueTo = static_cast<size_t>(atoll(wrapped.substr(29).begin()));

            // false
            getline(input, line);
            wrapped = string_view{line};
            mon.falseTo = static_cast<size_t>(atoi(wrapped.substr(30).begin()));

            // empty
            getline(input, line);

            monkeys.push_back(mon);
        }
    } else {
        cout << "Unable to open file";
    }

    for (int i{0}; i < 20; ++i) {
        for (monkey& m : monkeys) {
            while (!m.inv.empty()) {
                ++m.inspected;

                int newV{m.fun(m.inv.front())};
                newV /= 3;
                if (newV % m.test == 0)
                    monkeys[m.trueTo].inv.push(newV);
                else
                    monkeys[m.falseTo].inv.push(newV);

                m.inv.pop();
            }
        }
    }

    priority_queue<int> max;
    for (size_t i{0}; i < monkeys.size(); ++i) {
        cout << "Monkey " << i << " inspected items " << monkeys[i].inspected << " times." << endl;
        max.push(monkeys[i].inspected);
    }
    int max1 = max.top(); max.pop();
    int max2 = max.top(); max.pop();
    cout << "Monkey business " << max1 * max2 << endl;

    return 0;
}
