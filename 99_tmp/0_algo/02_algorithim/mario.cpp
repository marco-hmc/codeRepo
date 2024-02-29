#include <bits/stdc++.h>
using namespace std;

int solution(int M, int N, int K, vector<int> &L)
{
    vector<vector<int>> dp(N + 2, vector<int>(M + 1, 0));
    dp[0][M] = 1;
    for (int i = 1; i <= N + 1; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            for (int k = 1; k <= 3; k++)
                if (i - k >= 0 && dp[i - k][j] > 0)
                    dp[i][j] += dp[i - k][j];
        }
        if (i <= N && L[i])
        {
            for (int j = 1; j <= M; j++)
                dp[i][j - 1] = dp[i][j];
            dp[i][M] = 0;
        }
        // for (int j = 1; j <= M; j++)
        //     cout << "dp[" << i << "][" << j << "]=" << dp[i][j] << " " << endl;
    }
    int res = 0;
    for (int i = 1; i <= M; i++)
        res += dp[N + 1][i];
    return res;
}


int main()
{
    int M; //HP
    int N; //LENGTH
    int K; //LEN(L)
    cin >> M >> N >> K;
    vector<int> L(N + 1, 0); //broken plank

    for (int i = 0; i < K; ++i)
    {
        int tmp;
        cin >> tmp;
        L[tmp] = 1;
    }
    cout << solution(M, N, K, L) << endl;
    return 0;
}