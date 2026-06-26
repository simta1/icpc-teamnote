inline ll multiply(ll a, ll b, ll mod) { return __int128(a) * b % mod; }
ll binpow(ll a, ll n, ll mod) { //a ^ n % mod
    ll res = 1;
    while (n) {
        if (n & 1) res = multiply(res, a, mod);
        a = multiply(a, a, mod);
        n >>= 1;
    }
    return res;
}
// p=4k+3이고 n이 이차잉여라면 이산제곱근은 n^((p+1)/4)
ll tonelliShanks(ll n, ll p) { // O(log^2(p)) // x^2 === n (mod p) // 해가 없다면 -1 리턴
    assert (n >= 0 && n < p);
    if (!n) return 0;
    if (p == 2) return n;
    if (binpow(n, (p - 1) / 2, p) != 1) return -1;
    ll Q = p - 1, S = 0;
    while (~Q & 1) {
        Q >>= 1;
        ++S;
    }
    ll z = 2;
    while (binpow(z, (p - 1) / 2, p) != p - 1) ++z;
    ll M = S;
    ll c = binpow(z, Q, p);
    ll t = binpow(n, Q, p);
    ll R = binpow(n, (Q + 1) / 2, p);
    while (t != 1) {
        ll i = [&]() {
            ll tmp = t;
            for (int i = 1; i < M; i++) {
                tmp = multiply(tmp, tmp, p);
                if (tmp == 1) return i;
            }
        }();
        ll b = binpow(c, binpow(2, M - i - 1, p - 1), p); // c ^ (2 ^ (M - i - 1)), phi(p) = p - 1
        M = i;
        c = multiply(b, b, p);
        t = multiply(t, c, p);
        R = multiply(R, b, p);
    }
    return R; // (p - R) % p도 해가 되긴 함
}