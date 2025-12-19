#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

const std::string file = "input_p9.txt";
const std::regex dc(R"(\d+)");
const char del = ',';

int main() {
    std::ifstream f(file);
    std::string s;

    std::vector<std::array<unsigned int, 2>> data;
    while (getline(f, s)) {
        std::array<unsigned int, 2> p;
        int i = 0;
        int k = 0;
        std::sregex_iterator it(s.begin(), s.end(), dc), end;
        for (it; it != end; ++it) {
            std::string m = (*it)[0].str();
            p[k] = stoi(m);
            k++;
        }
        data.push_back(p);
    }

    unsigned long long max = 0;
    int n = data.size();
    unsigned long long areas[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            unsigned long long a =
                (unsigned long long)abs(data[i][0] - data[j][0] + 1) *
                (unsigned long long)abs(data[i][1] - data[j][1] + 1);
            if (a > max)
                max = a;
            areas[i][j] = a;
        }
    }

    std::cout << "Result (part 1): " << max << std::endl;

    return 0;
}