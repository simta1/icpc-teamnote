// 선공 승리조건 : xorSum = (n_1 ^ n_2 ^ ... ^ n_k) != 0
// 필승전략 : i번째에서 x개 가져갈때 next_xorSum = (xorsum ^ n_i ^ (n_i - x)) = 0
// x = n_i - (xorSum ^ n_i)
constexpr int MAX_N = 1000, MAX_X = 1000;
constexpr int MAX_GRUNDY = min(MAX_N, MAX_X);
vector<int> g(n + 1);
for (int i = 1; i <= n; i++) {
    bitset<MAX_GRUNDY + 1> bs;
    for (int j = 1; j <= min(i, x); j++) bs[g[i - j]] = 1;
    g[i] = (~bs)._Find_first();
}