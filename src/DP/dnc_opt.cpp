const int INF = 2e9;
vector dp(k + 1, vector<int>(n + 1, INF));
for (int i = 0; i <= k; i++) dp[i][0] = 0;

auto getDP = [&](auto &&getDP, int i, int s, int e, int optL, int optR) -> void {
    if (s > e) return;
    int m = s + e >> 1;
    int opt = -1;
    for (int j = max(lowerLimit(m), optL); j <= min(upperLimit(m), optR); j++) {
        int val = dp[i - 1][j] + f(j + 1, m);
        if (dp[i][m] > val) {
            dp[i][m] = val;
            opt = j;
        }
    }
    assert(~opt);
    getDP(getDP, i, s, m - 1, optL, opt);
    getDP(getDP, i, m + 1, e, opt, optR);
};

for (int i = 1; i <= k; i++) getDP(getDP, i, 1, n, 0, n - 1); // O(KN logN)
cout << dp[k][n];

// dp[i][k] = min_{low(k)<=j<=up(k)}{ dp[i - 1][j] + C(j, k) }
// dp[i][k]에 대해 dp[i - 1][j] + C(j, k)가 최소가 되는 가장 작은 j를 opt(i, k)라 할 때 opt(i, k) <= opt(i, k + 1)이어야 함
// 사각부등식(a<=b<=c<=d일 때 f(a,c)+f(b,d)<=f(a,d)+f(b,c)) 만족하면 opt(i, j) <= opt(i, j + 1)