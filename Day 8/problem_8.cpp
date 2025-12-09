#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <array>
#include <regex>
#include <algorithm>
#include <queue>
#include <tuple>

const std::string file = "input_p8.txt";
const std::regex dc(R"(\d+)");
const int num_pairs = 1000;

using HeapItem = std::tuple<unsigned long long, int, int>;

std::vector<HeapItem> k_smallest(const std::vector<std::vector<unsigned long long>>& arr, int k){
    std::priority_queue<HeapItem> maxHeap;
    std::vector<HeapItem> result;
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<i; j++){
            if (maxHeap.size() < k) {
                maxHeap.push(std::make_tuple(arr[i][j], i, j));
            } else if (arr[i][j] < std::get<0>(maxHeap.top())) {
                maxHeap.pop();
                maxHeap.push(std::make_tuple(arr[i][j], i, j));
            }
        }
    }
    while(!maxHeap.empty()){
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }

    return result;
}

std::vector<int> k_largest(const std::vector<int>& arr, int k){
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // min-heap
    std::vector<int> result;
    for(int i=0; i<arr.size(); i++){
        if (minHeap.size() < k) {
            minHeap.push(arr[i]);
        } else if (arr[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(arr[i]);
        }
    }
    while(!minHeap.empty()){
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    return result;
}

class Graph_Mat {
    std::vector<std::vector<unsigned long long>> adj_mat;

public:
    Graph_Mat(int n){
        adj_mat = std::vector<std::vector<unsigned long long>>(n, std::vector<unsigned long long>(n,0));
    }

    void add_edge(int u_int, int v_int, std::array<int, 3> u, std::array<int, 3> v){
        unsigned long long sq_dist = 0;
        for (int i = 0; i < 3; i++){
            sq_dist += pow(u[i] - v[i], 2);
        }

        adj_mat[u_int][v_int] = sq_dist;
        adj_mat[v_int][u_int] = sq_dist;
    }

        void add_edge(int u_int, int v_int){
        adj_mat[u_int][v_int] = 1;
        adj_mat[v_int][u_int] = 1;
    }

    void print(){
        // Get the number of vertices
        std::cout << "Adjacency Matrix for the Graph: " << std::endl;
        int n = adj_mat.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << adj_mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    const std::vector<std::vector<unsigned long long>> get_adj_mat() const {
        return adj_mat;
    }

};

class Graph_Lst{
    std::vector<int> parent;
    std::vector<std::vector<int>> adj_lst;
    std::vector<int> rank;

public:
    Graph_Lst(int n){
        parent = std::vector<int>(n);
        rank = std::vector<int>(n, 0);
        for(int i=0; i<n; i++) parent[i] = i;
    }

    int root(int a){
        if (a == parent[a]){
            return a;
        }

        return parent[a] = root(parent[a]);
    }

    void add_edge(int u, int v){
        int u_root = root(u);
        int v_root = root(v);

    if (u_root != v_root){
            // Union by rank
            if (rank[u_root] < rank[v_root]){
                parent[u_root] = v_root;
            } else if (rank[u_root] > rank[v_root]){
                parent[v_root] = u_root;
            } else {
                parent[u_root] = v_root;
                rank[v_root]++;
            }
            adj_lst.push_back({u, v});
        }
    }

    void print(){
        for(const auto& c:adj_lst){
            std::cout << c[0] << " -> " << c[1] << std::endl;
        }
    }

    std::vector<std::vector<int>> get_parent_sizes(){
        std::unordered_map<int,int> count;
        for(int i = 0; i < parent.size(); ++i){
            int r = root(i);
            ++count[r];
        }
        std::vector<std::vector<int>> o(2);
        for(const auto& kv : count){
            o[0].push_back(kv.first);
            o[1].push_back(kv.second);
        }
        return o;
    }
};

int main(){
    std::ifstream f(file);
    std::string s;

    std::vector<std::array<int, 3>> data;
    int n = 0;

    while (getline(f,s)){
        std::array<int, 3> p;
        int i = 0;
        int k = 0;
        std::sregex_iterator it(s.begin(), s.end(), dc), end;
        for (it; it!=end;++it){
            std::string m = (*it)[0].str();
            p[k] = stoi(m);
            k++;
        }
        data.push_back(p);
        n++;
    }

    Graph_Mat dist_graph(n);

    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if (j!=i){
                dist_graph.add_edge(i, j, data[i], data[j]);
            }
        }
    }

    // dist_graph.print();

    std::vector<HeapItem> smallest = k_smallest(dist_graph.get_adj_mat(), num_pairs);

    Graph_Lst connected(n);

    for(HeapItem e:smallest){
        connected.add_edge(std::get<1>(e), std::get<2>(e));
    }

    connected.print();

    std::vector<std::vector<int>> o = connected.get_parent_sizes();

    unsigned long total1 = 1;
    std::vector<int> largest_circuits = k_largest(o[1], 3);

    for (int& val:largest_circuits){
        total1*=val;
    }

    std::cout << "Result (part 1) " << total1 << std::endl;

    return 0;
}