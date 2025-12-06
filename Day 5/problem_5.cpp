#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

string file = "input_p5.txt";

bool comp(vector<unsigned long> a, vector<unsigned long> b){
    return a[0] < b[0];
}

int main(){
    ifstream f(file);
    string s;
    bool r = true;
    vector<vector<unsigned long>> ranges;
    vector<vector<unsigned long>> corrected_ranges;
    int total1 = 0;
    unsigned long long total2 = 0;

    while(getline(f, s)){
        if (s.size() == 0){
            r = false;

            sort(ranges.begin(), ranges.end(), comp);
            
            bool just_assigned = false;
            unsigned long range_l = ranges[0][0];
            unsigned long range_u = ranges[0][1];
            for (int i = 0; i<ranges.size()-1; i++) {
                if (just_assigned){
                    range_l = ranges[i][0];
                    range_u = ranges[i][1];
                    just_assigned = false;
                }
                if ((ranges[i+1][0]<=range_u)&&(ranges[i+1][1]>=range_u)){
                    range_u = ranges[i+1][1];
                } else if(ranges[i+1][0]>range_u) {
                    corrected_ranges.push_back({range_l, range_u});
                    just_assigned = true;
                }
            }
            corrected_ranges.push_back({range_l, range_u});

            continue;
        }

        if (r){
            char del = '-';
            auto pos = s.find(del);

            unsigned long l = stoul(s.substr(0, pos));
            unsigned long u = stoul(s.substr(pos+1));

            ranges.push_back({l, u});

        } else {
            unsigned long p = stoul(s);
            for (const auto &e : ranges) {
                if (p>=e[0] && p<=e[1]){
                    ++total1;
                    break;
                }
            }
        }
    }

    for (const auto &e : corrected_ranges) {
        total2 += e[1] - e[0] + 1;
    }


    cout<< "Result (part 1): "<< total1 << endl;  
    cout<< "Result (part 2): "<< total2 << endl;   

    return 1;
}