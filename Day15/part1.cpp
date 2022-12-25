#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

long long evalLine(long long line,
                   vector<pair<pair<long long, long long>, long long>> sensors,
                   vector<pair<long long, long long>> beacons) {
    set<long long> positions;
    for (auto [pos, dis] : sensors) {
        long long x = pos.first;
        long long y = pos.second;
        dis -= abs(y - line);

        for (long long i{x - dis}; i <= x + dis; ++i) {
            positions.insert(i);
        }
    }
    for (auto [pos, dis] : sensors)
        positions.erase(pos.first);
    for (auto pos : beacons)
        positions.erase(pos.first);
    return static_cast<long long int>(positions.size());
}

int main() {
    string line;
    ifstream input ("input.txt");
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

        cout << "Possible beacons in line: " << evalLine(2000000, sensors, beacons) << endl;
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
