#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

const std::string file = "input_p10.txt";
const std::regex dc(R"(\d+)");

const char del = ',';
const std::regex target_reg("\\[([.#]+)\\]");
const std::regex button_wirings_reg("\\([\\d,]+\\)");
const std::regex joltage_reqs("\\{([\\d,]+)\\}");

int solve_pt1(std::vector<int> data) {
    int result = 0;
    int target = data[0];
    std::vector<int> state_changes(data.begin() + 1, data.end());
    std::unordered_set<int> visited;
    std::vector<int> prev_outputs = {0};
    visited.insert(0);

    int l = 1;
    while (!prev_outputs.empty()) {
        std::vector<int> new_outputs;

        for (int prev_state : prev_outputs) {
            for (int change : state_changes) {
                int new_state = prev_state ^ change;
                if (new_state == target) {
                    return l;
                }

                if (!visited.count(new_state)) {
                    visited.insert(new_state);
                    new_outputs.push_back(new_state);
                }
            }
        }
        prev_outputs = new_outputs;
        l++;
    }
    return 0;
}

int solve_pt2(std::vector<std::vector<int>> data) {
    int result = 0;
    std::vector<int> target = data[0];
    std::vector<std::vector<int>> state_changes(data.begin() + 1, data.end());
    int l = target.size();
    std::vector<std::vector<int>> prev_outputs(1, std::vector<int>(l, 0));
    std::set<std::vector<int>> visited;
    visited.insert(std::vector<int>(l, 0));

    int count = 1;
    while (!prev_outputs.empty()) {
        std::vector<std::vector<int>> current_outputs;
        for (const auto &e : prev_outputs) {
            for (const auto &e1 : state_changes) {
                std::vector<int> result(l, 0);
                for (int i = 0; i < l; i++) {
                    result[i] = e[i] + e1[i];
                }
                if (result == target) {
                    return count;
                }
                if (visited.insert(result).second) {
                    current_outputs.push_back(result);
                }
            }
        }
        prev_outputs = current_outputs;
        count++;
        std::cout << "Count: " << count << std::endl;
    }

    return 0;
}

int main() {
    std::ifstream f(file);
    std::string s;

    std::vector<std::vector<std::vector<int>>> input_arr;
    std::vector<std::vector<int>> input;

    int k = 0;
    while (std::getline(f, s)) {
        // std::vector<std::vector<int>> row = {};
        std::vector<int> row = {};
        std::vector<std::vector<int>> row_arr = {};
        // Create target state
        std::sregex_iterator it_target(s.begin(), s.end(), target_reg);
        std::string m = (*it_target)[1].str();
        std::cout << m << std::endl;
        int num_indicators = m.size();
        int t = 0;
        for (int i = 0; i < num_indicators; i++) {
            t = (t << 1) | ((int)(m[i] == '#'));
        }
        // row.push_back({t});
        row.push_back(t);

        // Joltage reqs
        std::sregex_iterator it_joltage(s.begin(), s.end(), joltage_reqs);
        m = (*it_joltage)[1].str();
        std::vector<int> joltage_req_arr(num_indicators, 0);
        int i = 0;
        char del = ',';
        size_t start = 0;
        size_t e = m.find(del);

        while (e != std::string::npos) {
            joltage_req_arr[i] = stoi(m.substr(start, e - start));
            start = e + 1;
            e = m.find(del, start);
            i++;
        }
        joltage_req_arr[i] = stoi(m.substr(m.size() - 1, 1));
        row_arr.push_back(joltage_req_arr);

        // Create state changes
        std::vector<int> state_changes_bin;
        std::sregex_iterator it_button(s.begin(), s.end(), button_wirings_reg);
        std::sregex_iterator end;
        for (; it_button != end; ++it_button) {
            std::string m = (*it_button)[0].str();
            int state_change = 0;
            std::vector<int> state_change_arr(num_indicators, 0);
            for (int i = 0; i < m.size(); i++) {
                if (std::isdigit(m[i])) {
                    int idx = (int)(m[i] - '0');
                    // Reverse the bit position to match target encoding
                    state_change |= (1 << (num_indicators - 1 - idx));
                    state_change_arr[idx] = 1;
                }
            }
            // state_changes_bin.push_back(state_change);
            row.push_back(state_change);
            row_arr.push_back(state_change_arr);
        }

        // row.push_back(state_changes_bin);
        input.push_back(row);
        input_arr.push_back(row_arr);
    }

    int total1 = 0;
    for (std::vector<int> e : input) {
        int l = solve_pt1(e);
        total1 += l;
    }
    std::cout << "Result (part 1): " << total1 << std::endl;

    int total2 = 0;
    int logger = 0;
    for (std::vector<std::vector<int>> e : input_arr) {
        int l = solve_pt2(e);
        std::cout << logger << " " << l << std::endl;
        total2 += l;
        logger++;
    }

    std::cout << "Result (part 2): " << total2 << std::endl;

    return 0;
}