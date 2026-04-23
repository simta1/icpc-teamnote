vector dp(n + 1, vector<ll>(n + 1, INF));
vector opt(n + 1, vector<int>(n + 1));
for (int i = 1; i <= n; i++) {
    dp[i][i] = 0;
    opt[i][i] = i;
}
for (int len = 2; len <= n; len++) {
    for (int s = 1, e = len; e <= n; ++s, ++e) {
        for (int m = opt[s][e - 1]; m <= opt[s + 1][e] && m < e; m++) {
            ll val = dp[s][m] + dp[m + 1][e] + cost[s][e];
            if (dp[s][e] > val) {
                dp[s][e] = val;
                opt[s][e] = m;
            }
        }
    }
}
cout << dp[1][n];
// dp[i][j] = min_{i<=k<j}{ dp[i][k] + dp[k+1][j] + C(i, j) }
// a<=b<=c<=d일 때 C(a,c)+C(b,d)<=C(a,d)+C(b,c), C(b, c) <= C(a, d)를 만족하면
// dp[i][j]가 최소가 되는 k를 opt[i][j]라 할 때 opt[s][e - 1] <= opt[s][e] <= opt[s + 1][e]
