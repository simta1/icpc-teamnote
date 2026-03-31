vector<ll> inv(n + 2, 1);
for (int i = 2; i <= n + 1; ++i) inv[i] = inv[p % i] * (p - p / i) % p;
vector<ll> cat(n + 1, 1);
for (int i = 2; i <= n; ++i) cat[i] = cat[i - 1] * (4 * i - 2) % p * inv[i + 1] % p;
// C0 = 1, C1 = 1, C2 = 2, C3 = 5
// C_n = 2nCn / (n + 1) = C_{n - 1} * (4n - 2) / (n + 1)