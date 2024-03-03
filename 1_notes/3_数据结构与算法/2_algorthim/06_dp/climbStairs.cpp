#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int solution_1(int n){
        int len = max(3, n);
        int dp[len + 1];
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i < n; i++){
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    int solution_2(int n){
        int len = max(3, n);
        int dp[len + 1];
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i < n; i++){
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    void method_test(int(* f)(int a)){
        cout<<"Testing solution "<< f(2)<<endl;
        cout<<"Testing solution "<< f(3)<<endl;
        cout<<"Testing solution "<< f(4)<<endl;
    }

    void test(){
        method_test(solution_1);
        method_test(solution_2);
    }
};

int main(){
    while(1){
        string str;
        getline(cin, str, '\n');
        if (str == "")
            break;
        int n = atoi(str.c_str());
        Solution s;
        s.test();
    }
}