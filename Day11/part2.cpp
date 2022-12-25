#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <functional>
#include <set>

using namespace std;

struct monkey {
    queue<long long> inv;
    function<long long(long long)> fun;
    long long test;
    size_t trueTo;
    size_t falseTo;

    long inspected;
};

int main() {
    string line;
    ifstream input ("input.txt");
    vector<monkey> monkeys;
    set<long long> divisors;
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
                    mon.fun = [](long long a){ return a * a; };
                else if (wrapped[23] == '+')
                    mon.fun = [](long long a){ return a + a; };
                else
                    cout << "Error" << endl;
            } else {
                int val = atoi(wrapped.substr(25).begin());
                if (wrapped[23] == '*')
                    mon.fun = [val](long long a){ return a * val; };
                else if (wrapped[23] == '+')
                    mon.fun = [val](long long a){ return a + val; };
                else
                    cout << "Error" << endl;
            }

            // test
            getline(input, line);
            wrapped = string_view{line};
            mon.test = atol(wrapped.substr(21).begin());
            divisors.insert(mon.test);

            // true
            getline(input, line);
            wrapped = string_view{line};
            mon.trueTo = static_cast<size_t>(atoi(wrapped.substr(29).begin()));

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

    long commonMultiple{1};
    for (long long d : divisors)
        commonMultiple *= d;
    for (int i{0}; i < 10000; ++i) {
        for (monkey& mon : monkeys) {
            while (!mon.inv.empty()) {
                ++mon.inspected;

                long long newV{mon.fun(mon.inv.front())};
                newV %= commonMultiple;
                if (newV % mon.test == 0)
                    monkeys[mon.trueTo].inv.push(newV);
                else
                    monkeys[mon.falseTo].inv.push(newV);

                mon.inv.pop();
            }
        }
    }

    cout << "Common multiptle is " << commonMultiple << endl;
    priority_queue<long long> max;
    for (size_t i{0}; i < monkeys.size(); ++i) {
        cout << "Monkey " << i << " inspected items " << monkeys[i].inspected << " times." << endl;
        max.push(monkeys[i].inspected);
    }
    long long max1 = max.top(); max.pop();
    long long max2 = max.top(); max.pop();
    cout << "Monkey business " << max1 * max2 << endl;

    return 0;
}
