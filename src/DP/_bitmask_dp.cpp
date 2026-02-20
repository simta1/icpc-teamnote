vector<ld> dp(1 << n, DEFAULT_VALUE);
dp[0] = INIT_VALUE;
for (int bit = 1; bit < (1 << n); bit++) { // O(N 2^{N-1})   
    int cnt = __builtin_popcount(bit);
    for (int tmp = bit; tmp; tmp &= tmp - 1) {
        int i = __builtin_ctz(tmp);
        dp[bit] = best(dp[bit], func(dp[bit ^ (1 << i)], i, cnt)); // best()는 min, max, add등등..
    }
}
cout << dp.back();

// 역추적
function<void(int)> trace = [&](int bit) {
    cout << bit << " ";
    if (!bit) return;
    
    int cnt = __builtin_popcount(bit);
    for (int tmp = bit; tmp; tmp &= tmp - 1) {
        int i = __builtin_ctz(tmp);
        if (check(dp[bit ^ (1 << i)], i, cnt)) {
            trace(bit ^ (1 << i));
            return;
        }
    }

    assert(false);
};