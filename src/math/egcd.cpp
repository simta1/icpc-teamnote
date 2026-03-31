tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = egcd(b, a % b);
    return {y, x - (a / b) * y, g};
}
ll modInv(ll a, ll b) {
    auto [x, y, g] = egcd(a, b); //ax + by = g
    if (g == 1) return (x + b) % b;
    return -1;
} // modInv(n, MOD)
vector<ll> inv(n + 1, 1);
for (int i = 2; i <= n; ++i) inv[i] = inv[p % i] * (p - p / i) % p;