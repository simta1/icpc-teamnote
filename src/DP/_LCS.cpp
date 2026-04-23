// 최장 공통 부분 수열(Longest Common Subsequence), 연속하게 안 골라도 됨
int LCS(const string &a, const string &b) { // O(NM)
    int n = a.size(), m = b.size();
    vector dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}
// bitset 사용 시 O(NM/w) 가능

// 최장 공통 부분 문자열(Longest Common Substring), 연속하게 골라야 함
int LCS(const string &a, const string &b) { // O(NM)
    int res = 0;
    int n = a.size(), m = b.size();
    vector dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            res = max(res, dp[i][j]);
        }
    }
    return res;
}
// suffix array + lcp array 사용 시 O((N+M)log(N+M)) 가능