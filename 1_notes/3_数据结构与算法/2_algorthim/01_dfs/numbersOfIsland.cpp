#include <bits/stdc++.h>
using namespace std;


class Solution{
public:
    int solve(vector<vector<char> > &grid){
        
    }
};

void init_test(vector<vector<char>>& grid) {
    grid.push_back({'1', '1', '0', '0', '0'});
    grid.push_back({'0', '1', '0', '1', '1'});
    grid.push_back({'0', '0', '0', '1', '1'});
    grid.push_back({'0', '0', '0', '0', '0'});
    grid.push_back({'0', '0', '1', '1', '1'});
}

void algo_test(vector<vector<char>>& grid) {
    Solution s;
    s.solve(grid);
}

int main(){
    int n, m;
    cin>>n>>m;
    vector<vector<char> > grid;
    init_test(grid);
    
}