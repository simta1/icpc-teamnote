ll isqrt(ll n) {
    assert(n >= 0);
    if (n == 0) return 0LL;
    ll x = sqrtl(n);
    while ((x + 1) <= n / (x + 1)) ++x;
    while (x > n / x) --x;
    return x;
}
pll cornacchia(ll m, ll d) { // x^2 + d y^2 = m // m은 소수, d>0 // 해 없으면 {-1, -1} // O(log^2 m)
    assert(m >= 2 && d > 0);
    ll r0 = tonelliShanks((m - d % m) % m, m);
    if (r0 == -1) return {-1, -1};
    ll prev = m, cur = r0;
    while ((__int128)cur * cur >= m) {
        ll next = prev % cur;
        prev = cur;
        cur = next;
    }
    ll x = cur;
    ll rem = m - x * x;
    if (rem < 0 || rem % d != 0) return {-1, -1};
    ll y2 = rem / d;
    ll y = isqrt(y2);
    if ((__int128)y * y != y2) return {-1, -1};
    return {x, y};
}