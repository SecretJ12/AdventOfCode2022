#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

using namespace std;


int main() {
    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        uint64_t contained{0};
        while (getline(input, line)) {
            string_view view{line};
            size_t del{view.find(',')};
            string_view A = view.substr(0, del);
            string_view B = view.substr(del+1, view.length());
            del = A.find('-');
            string_view Al = A.substr(0, del);
            string_view Ar = A.substr(del+1, A.length());
            del = B.find('-');
            string_view Bl = B.substr(0, del);
            string_view Br = B.substr(del+1, B.length());

            long long nAl = atoll(Al.begin());
            long long nAr = atoll(Ar.begin());
            long long nBl = atoll(Bl.begin());
            long long nBr = atoll(Br.begin());
            // cout << nAl << "-" << nAr << "," << nBl << "-" << nBr << "\n";
            if ((nAl <= nBl && nBr <= nAr) || (nBl <= nAl && nAr <= nBr))
                ++contained;
        }
        input.close();

        cout << contained << '\n';
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
