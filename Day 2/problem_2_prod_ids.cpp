#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <math.h>
#include <cmath>

using namespace std;

string file = "input_p2.txt";
string s;
char del1 = ',';
char del2 = '-';

unsigned long long part_1(string file){
    ifstream f(file);

    unsigned long long total = 0;

    while (getline(f, s, del1)){
        auto pos = s.find(del2);

        string l = s.substr(0, pos);
        string u = s.substr(pos+1);

        cout << "Range: " << s.substr(0, pos) << " - " << s.substr(pos+1) << endl;

        unsigned long l_int = stol(l);
        unsigned long u_int = stol(u);

        unsigned long i = l_int;

        while(i <= u_int){
            float len_check_float = log10(i);
            int id_len = ceil(len_check_float);

            if(len_check_float == id_len){++id_len;}
            if(id_len%2 != 0){
                i = pow(10,id_len);
                continue;
            }

            int first_half_digits = floor(i/pow(10,(id_len/2)));
            int last_half_digits = i-first_half_digits*pow(10,(id_len/2));


            if(first_half_digits==last_half_digits){
                cout << "id " << i << " added" << endl;
                total += i;
            }

            // cout << i << " " << first_half_digits << " " << last_half_digits << endl;

            ++i;
        }
    }
    f.close();

    return total;
}

unsigned long long part_2(string file){
    ifstream f(file);

    unsigned long long total = 0;

    while (getline(f, s, del1)){
        auto pos = s.find(del2);

        string l = s.substr(0, pos);
        string u = s.substr(pos+1);

        cout << "Range: " << s.substr(0, pos) << " - " << s.substr(pos+1) << endl;

        unsigned long l_int = stol(l);
        unsigned long u_int = stol(u);

        unsigned long i = l_int;

        while(i <= u_int){
            // cout << "Checking " << i << endl;
            string num = to_string(i);
            int id_len = num.length();

            // float len_check_float = log10(i);
            // int id_len_check = ceil(len_check_float);
            // if(len_check_float == id_len_check){++id_len_check;}

            // if(id_len != id_len_check){
            //     cout << i << endl;
            // }

            for(int j = 2; j <= id_len; ++j){
                if(id_len%j != 0){
                    continue;
                }

                string first_pattern = num.substr(0, id_len/j);
                string new_pattern;
                int k;
                for(k=1; k<j; k++){
                    new_pattern = num.substr(k*id_len/j, id_len/j);
                    if (first_pattern!=new_pattern){
                        break;
                    }
                }
                if (first_pattern == new_pattern){
                    // cout << "id " << i << " added" << endl;
                    total += i;
                    break;
                }

                // float num = i;
                // num = i;
                // unsigned long first_set_digits = floor(i/pow(10,id_len - (id_len/j)));
                // unsigned long new_set_digits;
                // int k = 0;

                // for(k=0; k < j-1; ++k){
                //     num -= first_set_digits*pow(10,id_len - (k+1)*(id_len/j));
                //     // float helper = num/pow(10, )
                //     new_set_digits = floor(num/pow(10, id_len-(k+2)*id_len/j));
                //     if (first_set_digits != new_set_digits){
                //         break;
                //     }
                // }
                // if (first_set_digits == new_set_digits && k == j-1){
                //     cout << "id " << i << " added" << endl;
                //     total += i;
                //     break;
                // }
                // cout << i << " " << first_half_digits << " " << last_half_digits << endl;
            }

            ++i;
        }
    }
    f.close();

    return total;
}

int main(){
    unsigned long long total1 = part_1(file);
    cout<< "Result (part 1): "<< total1 << endl;

    unsigned long long total2 = part_2(file);
    cout<< "Result (part 2): "<< total2 << endl;

    return 0;
}