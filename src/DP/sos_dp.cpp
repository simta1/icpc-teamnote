template <typename T>
vector<T> sosDP(int n, const vector<T> &v) { // O(N 2^N)
    assert(v.size() == (1 << n));
    vector<T> dp(v);
    for (int axis = 1; axis < (1 << n); axis <<= 1) {
        for (int mask = axis; mask < (1 << n); mask = (mask + 1) | axis) dp[mask] += dp[mask ^ axis];
    }
    return dp;
}

// 아래랑 같은 의미
for (int i = 0; i < n; i++) {
    for (int mask = 0; mask < (1 << n); mask++) if (mask >> i & 1) dp[mask] += dp[mask ^ (1 << i)];
}