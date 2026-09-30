constexpr ll P = 998'244'353;
constexpr int N = 2'000'005;
static ll inv[N + 2] = {1, 1};
for (int i = 2; i <= N + 1; ++i) inv[i] = inv[P % i] * (P - P / i) % P;
static ll cat[N + 1] = {1, 1};
for (int i = 2; i <= N; ++i) cat[i] = cat[i - 1] * (4 * i - 2) % P * inv[i + 1] % P;
// C0 = 1, C1 = 1, C2 = 2, C3 = 5
// C_n = 2nCn / (n + 1) = C_{n - 1} * (4n - 2) / (n + 1)
