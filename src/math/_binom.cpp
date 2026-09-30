constexpr int N = 1000;
static ll comb[N + 1][N + 1] = {1};
for (int i = 1; i <= N; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
        comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        if (comb[i][j] >= MOD) comb[i][j] -= MOD;
    }
}

constexpr ll MOD = 998'244'353;
constexpr int N = 2'000'005;
static ll fac[N + 1] = {1}, ifac[N + 1]{};
for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
ifac[N] = modInv(fac[N], MOD);
for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
auto nCr = [&](int n, int r) {
    return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
};