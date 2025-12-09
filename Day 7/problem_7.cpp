#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>

const std::string file = "input_p7.txt";

int main(){
    std::ifstream f(file);
    std::string s;
    bool first_line = true;
    std::vector<std::vector<int>> beam_path;
    std::vector<std::vector<int>> obstacles;
    std::vector<std::vector<int>> beam_idxs;
    std::vector<std::vector<unsigned long>> timelines;
    int r = 0;
    int total1 = 0;
    unsigned long total2 = 0;

    while(getline(f, s)){
        std::vector<int> row(s.size(), 0);
        // row.assign(0, s.size());
        if (first_line){
            obstacles.push_back(row);
            auto pos = s.find("S");
            std::cout<<pos<<std::endl;
            beam_idxs.push_back({(int)pos});
            row[pos] = 1;
            beam_path.push_back(row);
            first_line = false;
        } else {
            beam_path.push_back(row);
            char o = '^';
            int i = 0;
            while ((i = s.find(o, i + 1)) != std::string::npos){
                row[i] = 1;
            }
            obstacles.push_back(row);
        }

        r++;
    }

    timelines.push_back({1});
    for(int i=1; i<obstacles.size();++i){
        std::vector<int> obs_row = obstacles[i];
        std::vector<int> new_beams;
        std::vector<unsigned long> new_timelines;
        std::cout << i << "/" << obstacles.size()<<std::endl;
        int k = 0;
        for(auto idx : beam_idxs[i-1]){
            if (obs_row[idx] == 1){
                total1++;
                if ((obs_row[idx-1]==0)){
                    auto it = std::find(new_beams.begin(), new_beams.end(), idx-1);
                    if (it == new_beams.end()){
                        new_beams.push_back(idx-1);
                        new_timelines.push_back(timelines[i-1][k]);
                    } else {
                        int beam_idx_int = std::distance(new_beams.begin(), it);
                        new_timelines[beam_idx_int] += timelines[i-1][k];
                    }
                }
                if ((obs_row[idx+1]==0)){

                    if (std::find(new_beams.begin(), new_beams.end(), idx+1) == new_beams.end()){
                        new_beams.push_back(idx+1);
                        new_timelines.push_back(timelines[i-1][k]);
                    }
                }
            } else {
                auto it = std::find(new_beams.begin(), new_beams.end(), idx);
                if (it == new_beams.end()){
                    new_beams.push_back(idx);
                    new_timelines.push_back(timelines[i-1][k]);
                } else {
                    int beam_idx_int = std::distance(new_beams.begin(), it);
                    new_timelines[beam_idx_int] += timelines[i-1][k];
                }

                // if(it == new_beams.end()){
                //     new_beams.push_back(idx);
                // }
            }
            k++;
        }
        timelines.push_back(new_timelines);
        beam_idxs.push_back(new_beams);
    }

    for(int i=0; i<timelines[obstacles.size()-1].size(); i++){
        total2 += timelines[obstacles.size()-1][i];
    }

    return 0;
}