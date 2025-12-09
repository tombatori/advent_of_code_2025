#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <math.h>
#include <cmath>

using namespace std;

string file = "input_p3.txt";

unsigned long part1(){
    ifstream f(file);

    unsigned long total = 0;

    string(s);

    while(getline(f, s)){
        int l = s.size();
        int entries[l];
        for(int i = 0; i<l; ++i){
            entries[i] = stoi(s.substr(i, 1));
        }

        auto first_max = max_element(entries, entries+(l-1));

        auto second_max = max_element(entries+((first_max - entries)+1), entries+l);

        total += *first_max*10 + *second_max;

    }

    return total;
}

unsigned long long part2(){
    ifstream f(file);

    unsigned long total = 0;
    int joltage_length = 12;

    string(s);

    while(getline(f, s)){
        int l = s.size();
        int entries[l];
        for(int i = 0; i<l; ++i){
            entries[i] = stoi(s.substr(i, 1));
        }


        int jolt_vals[joltage_length];
        auto next_lower_index = 0;
        for(int i=0; i<joltage_length; ++i){
            auto new_max = max_element(entries+next_lower_index, entries+(l-(joltage_length-1-i)));
            jolt_vals[i] = *new_max;
            next_lower_index = new_max - entries + 1;
        }

        for(int i=0; i<joltage_length; ++i){
            total += jolt_vals[i]*pow(10, joltage_length-1-i);
        }

    }
    return total;
}

int main(){
    unsigned long total1 = 0;
    unsigned long long total2 = 0;

    total1 = part1();
    total2 = part2();

    cout<< "Result (part 1): "<< total1 << endl;
    cout<< "Result (part 2): "<< total2 << endl;

    return 0;
}