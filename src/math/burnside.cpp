ll bracelet(int c, int n) { // 색깔 c종류 염주순열 개수
    vector<ll> powc(n + 1, 1);
    for (int i = 1; i <= n; i++) powc[i] = powc[i - 1] * c;
    ll a = powc[n / 2 + 1];
    ll b = powc[n / 2];
    ll ans = (n & 1) ? n * a : n / 2 * (a + b);
    for (int i = 0; i < n; i++) ans += powc[__gcd(i, n)];
    return ans / (2 * n);
}