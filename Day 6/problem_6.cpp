// Terrible solution, to be redone

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <regex>

using namespace std;

const string file = "input_p6.txt";
const regex digit_code(R"(\d+)");
const regex digit_code_spaces(R"(\d+\s+)");
const regex operator_code(R"([\*\+])");

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> to_int_matrix(const vector<vector<string>>& nums) {
    vector<vector<int>> result;
    result.reserve(nums.size());

    for (const auto& row : nums) {
        vector<int> int_row;
        int_row.reserve(row.size());

        for (auto s : row) { // copy each string
            int_row.push_back(stoi(s));
        }
        result.push_back(move(int_row));
    }

    return result;
}

unsigned long long evaluate_result(string s, vector<vector<int>> numbers){
    unsigned long long total = 0;
    int i = 0;
    sregex_iterator it_op(s.begin(), s.end(), operator_code), end;
    for(it_op; it_op!=end;++it_op){
        string matched = (*it_op)[0].str();
        // cout << matched << endl;
        unsigned long h;
        if (matched=="*"){
            h = 1;
            for (int j=0; j<numbers[i].size(); ++j){
                h *= numbers[i][j];
            }

        } else if (matched=="+"){
            h = 0;
            for (int j=0; j<numbers[i].size(); ++j){
                h += numbers[i][j];
            }
        }
        total += h;
        i++;
    }
    return total;
}

int main(){
    unsigned long long total = 0;

    vector<vector<int>> numbers_part1;

    ifstream f(file);
    string s;
    bool first_line = true;
    int num_entries=0;

    vector<int> input_grid;
    bool found_delimiters = false;

    int total_rows = 0;

    while(getline(f,s)){
        total_rows++;
        int i = 0;
        sregex_iterator it(s.begin(), s.end(), digit_code), end;
        sregex_iterator it_s(s.begin(), s.end(), digit_code_spaces);
        if (it!=end){
            for(it; it!=end;++it){
                string matched = (*it)[0].str();
                int val = stoi(matched);
                if (first_line){
                    numbers_part1.push_back({val});
                    ++num_entries;
                } else {
                    numbers_part1[i].push_back(val);
                    i++;
                }
            }

            if (!found_delimiters){
                for(int k=0; k<s.size(); ++k){
                    if (first_line){
                        if (s[k]==' '){
                            input_grid.push_back(1);
                        } else {
                            input_grid.push_back(0);
                        }
                    } else {
                        if (input_grid[k]==1 && s[k]!=' '){
                            input_grid[k] = 0;
                        }
                    }
                }
            }

            int num_entries_found = accumulate(input_grid.begin(), input_grid.end(), 0);
            if (num_entries_found==num_entries-1){found_delimiters=true;}

        } else {
            total = evaluate_result(s, numbers_part1);
        }
        first_line = false;
    }
    f.close();

    ifstream g(file);
    vector<string> numbers;
    vector<vector<string>> numbers_part2;
    first_line = true;
    input_grid.push_back(1);
    int row_count = 0;
    unsigned long long total2;

    while(getline(g,s)){
        if (total_rows==row_count+1){
            vector<vector<int>> numbers_part2_int = to_int_matrix(numbers_part2);
            total2 = evaluate_result(s, numbers_part2_int);
            continue;
        }
        int j = 0;
        int k = 0;
        for (int i=0; i<s.size()+1; ++i){
            if (input_grid[i]==1){
                j=0;
                k++;
                if (first_line) {
                    numbers_part2.push_back(numbers);
                    numbers = {};
                }
                continue;
            }
            if (first_line){
                if(s.substr(i, 1)==" "){
                    numbers.push_back("0");
                } else {
                    numbers.push_back(s.substr(i, 1));
                }
            } else {
                cout << k << " " << j << endl;
                if(s.substr(i, 1)!=" "){
                    numbers_part2[k][j] = numbers_part2[k][j].append(s.substr(i,1));
                }
            }
            

            j++;
        }
        first_line = false;
        row_count++;
    }

    cout << total << endl;
    cout << total2 << endl;

    return 1;
}