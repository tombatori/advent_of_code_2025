#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

string file = "input_p4.txt";

int main(){
    ifstream f(file);
    string s;

    vector<vector<int>> kernel = {{1,1,1},{1,0,1},{1,1,1}};
    vector<vector<int>> warehouse_floor;
    vector<vector<int>> next_warehouse_floor;
    vector<vector<int>> convolution_output;
    vector<int> padding_row;
    vector<int> convolution_row;
    int x;

    bool first_row = true;
    while(getline(f, s)){
        if(first_row){
            x = s.size();
            padding_row.assign(x+2, 0);
            convolution_row.assign(x, 0);
            warehouse_floor.push_back(padding_row);
            first_row=false;
        }
        vector<int> row = {};
        row.push_back(0);
        for(int j=0; j < s.size(); ++j){
            if (s[j] == '.'){
                row.push_back(0);
            } else if (s[j] == '@') {
                row.push_back(1);
            }
        }
        row.push_back(0);

        warehouse_floor.push_back(row);
        convolution_output.push_back(convolution_row);
    }
    warehouse_floor.push_back(padding_row);
    next_warehouse_floor = warehouse_floor;

    int y = warehouse_floor.size()-2;

    int total = 0;
    int prev_total = -1;
    int total1 = 0;
    bool first = true;

    while(prev_total!=total){
        prev_total = total;

        // For each pixel in the image
        for(int i=1;i<y+1;++i){
            for(int j=1;j<x+1;++j){
                int free_spaces = 8;
                // Convolve if there is a roll
                if(warehouse_floor[i][j]==1){
                    for(int i_prime=-1;i_prime<=1;++i_prime){
                        for(int j_prime=-1;j_prime<=1;++j_prime){
                            free_spaces -= warehouse_floor[i+i_prime][j+j_prime]*kernel[i_prime+1][j_prime+1];
                        }
                    }
                    convolution_output[i-1][j-1] = free_spaces;
                    if (free_spaces >= 5){
                        next_warehouse_floor[i][j] = 0;
                        ++total;
                    }
                }
            }
        }
        warehouse_floor = next_warehouse_floor;
        if (first){
            total1=total;
            first = false;
        }
    }

    cout<< "Result (part 1): "<< total1 << endl;
    cout<< "Result (part 2): "<< total << endl;

    return 0;
}