#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

#if true
static const long long RANGE = 4000000;
static const long long ExRANGE = 4194304;
static const string file = "input.txt";
#else
static const long long RANGE = 20;
static const long long ExRANGE = 32;
static const string file = "testinput.txt";
#endif


bool test(long long x, long long y, pair<pair<long long, long long>, long long> sensor) {
    auto& [pos, dis] = sensor;
    return abs(pos.first-x)+abs(pos.second-y) <= dis;
}

void print(long long x, long long y, long long r) {
    for (int i{0}; i <= RANGE; ++i) {
        for (int j{0}; j <= RANGE; ++j) {
            if (i == 14 && j == 11)
                cout << "x";
            else if (i >= x && i < x+r && j >= y && j < y+r)
                cout << "#";
            else
                cout << ".";

        }
        cout << endl;
    }
}

void testSquare(long long x, long long y, long long r,
                   vector<pair<pair<long long, long long>, long long>>& sensors,
                   vector<pair<long long, long long>>& beacons) {
    if (x > RANGE || y > RANGE) {
        return;
    }

    for (auto& s : sensors) {
        if (test(x, y, s) && test(x+r-1, y, s) && test(x+r-1, y+r-1, s) && test(x, y+r-1, s))
            return;
    }
    if (r == 1) {
        cout << x << "-" << y << endl;
        cout << 4000000*x+y << endl;
        return;
    }

    testSquare(x, y, r/2, sensors, beacons);
    testSquare(x+r/2, y, r/2, sensors, beacons);
    testSquare(x+r/2, y+r/2, r/2, sensors, beacons);
    testSquare(x, y+r/2, r/2, sensors, beacons);
}

int main() {
    string line;
    ifstream input (file);
    if (input.is_open()) {
        vector<pair<pair<long long, long long>, long long>> sensors;
        vector<pair<long long, long long>> beacons;
        while (getline(input, line)) {
            string_view wLine{line};

            size_t pos1 = wLine.find('=');
            size_t pos2 = wLine.find(',');
            long long sX = atoll(wLine.substr(pos1+1, pos2).begin());
            wLine = wLine.substr(pos2+1);

            pos1 = wLine.find('=');
            pos2 = wLine.find(':');
            long long sY = atoll(wLine.substr(pos1+1, pos2).begin());
            wLine = wLine.substr(pos2+1);

            pos1 = wLine.find('=');
            pos2 = wLine.find(',');
            long long bX = atoll(wLine.substr(pos1+1, pos2).begin());
            wLine = wLine.substr(pos2+1);

            pos1 = wLine.find('=');
            pos2 = wLine.find(':');
            long long bY = atoll(wLine.substr(pos1+1, pos2).begin());

            sensors.emplace_back(make_pair(sX, sY), abs(sX-bX)+abs(sY-bY));
            beacons.emplace_back(bX, bY);
        }

        testSquare(0, 0, ExRANGE, sensors, beacons);
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
