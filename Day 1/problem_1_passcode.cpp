#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;

int get_length(string file){
    ifstream f(file);

    string s;
    int n_lines = 0;
    while(getline(f, s)){
        ++n_lines;
    }
    // cout << n_lines << endl;

    f.close();
    return n_lines;
}

vector<int> read_file(string file, int n_lines){
    ifstream g(file);


    string s;
    vector<int> moves;
    moves.resize(n_lines);

    int i = 0;
    size_t pos = 1;
    while (getline(g, s)){
        if (s[0]=='L'){
            moves[i] = -1*stoi(s.substr(1));
        }
        else{
            moves[i] = stoi(s.substr(1));
        }
        ++i;
    }   

    g.close();
    
    return moves;
}

int part1(int n_lines, vector<int> moves, int start){
    int passcode = 0;
    int cumulative = start;

    for(int i=0; i<n_lines; ++i){
        cumulative += moves[i];
        if (cumulative%100 == 0){
            ++passcode;
        }
        // cout << cumulative << endl;
    }

    return passcode;
}

int part2(int n_lines, vector<int> moves, int start){
    int passcode = 0;
    int cumulative = start;
    int crossings = 0;

    for(int i=0; i<n_lines; ++i){
        // cout << "move " << moves[i] << " passcode "<< passcode << endl;

        if (moves[i]>0){
            crossings = (cumulative+moves[i])/100;
        }
        else{
            int m = -moves[i];
            crossings = (((100-cumulative)%100)+m)/100;
        }
        passcode += crossings;

        cumulative = (cumulative+moves[i])%100;
        if (cumulative<0){
            cumulative += 100;
        }
        
        // cout << "corrected to " << cum << " passcode "<< passcode << endl;
    }

    return passcode;
}

int main()
{
    string file = "input_p1.txt";
    int n_lines;
    n_lines = get_length(file);

    vector<int> moves;
    moves = read_file(file, n_lines);

    int start = 50;
    int passcode1 = part1(n_lines, moves, start);
    int passcode2 = part2(n_lines, moves, start);

    cout << "Passcode (part 1): " << passcode1 << endl;
    cout << "Passcode (part 2): " << passcode2 << endl;

    return 0;
}