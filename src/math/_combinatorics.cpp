constexpr int N = 1000;
static ll comb[N + 1][N + 1] = {1};
for (int i = 1; i <= N; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
        comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        if (comb[i][j] >= MOD) comb[i][j] -= MOD;
    }
}

tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = egcd(b, a % b);
    return {y, x - (a / b) * y, g};
}
ll modInv(ll a, ll b) {
    auto [x, y, g] = egcd(a, b);
    return g != 1 ? -1 : (x + b) % b;
} // modInv(n, MOD)

constexpr ll MOD = 998'244'353;
constexpr int N = 2'000'005;
static ll fac[N + 1] = {1}, facInv[N + 1]{};
for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
facInv[N] = modInv(fac[N], MOD);
for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;
auto nCr = [&](int n, int r) {
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
};

constexpr ll P = 998'244'353;
constexpr int N = 2'000'005;
static ll inv[N + 2] = {1, 1};
for (int i = 2; i <= N + 1; ++i) inv[i] = inv[P % i] * (P - P / i) % P;
static ll cat[N + 1] = {1, 1};
for (int i = 2; i <= N; ++i) cat[i] = cat[i - 1] * (4 * i - 2) % P * inv[i + 1] % P;
// C0 = 1, C1 = 1, C2 = 2, C3 = 5
// C_n = 2nCn / (n + 1) = C_{n - 1} * (4n - 2) / (n + 1)