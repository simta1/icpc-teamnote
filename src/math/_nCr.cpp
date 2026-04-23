constexpr int N = 1000;
static ll comb[N + 1][N + 1] = {1};
for (int i = 1; i <= N; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
        comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        if (comb[i][j] >= MOD) comb[i][j] -= MOD;
    }
}
