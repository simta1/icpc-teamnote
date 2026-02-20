int n;
vector<vector<int> > table(__lg(maxK) + 1, vector<int>(n + 1));
for (int i = 1; i <= n; i++) cin >> table[0][i];
for (int i = 1; i < table.size(); i++) { // O(N log(maxK))   
    for (int j = 1; j <= n; j++) table[i][j] = table[i - 1][table[i - 1][j]];
}

auto query = [&](T k, int x) { // f^k[x] // O(logK)
    while (k) {
        x = table[__builtin_ctz(k)][x];
        k &= (k - 1);
    }
    return x;
};