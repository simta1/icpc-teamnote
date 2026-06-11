// mod <= INT_MAX
ll binpow(ll a, ll n, ll mod) { // a ^ n % mod
    ll res = 1;
    while (n) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

// mod <= LLONG_MAX
ll multiply(ll a, ll b, ll mod) {
    return __int128(a) * b % mod;
}

ll power(ll a, ll n, ll mod) { //a ^ n % mod
    ll res = 1;
    while (n) {
        if (n & 1) res = multiply(res, a, mod);
        a = multiply(a, a, mod);
        n >>= 1;
    }
    return res;
}

// 
pll tanNth(ll a, ll b, ll n, ll mod) { // tanT = a / b, tan(nT) = ?
    ll ra = 0, rb = 1;
    
    while (n) {
        if (n & 1) tie(ra, rb) = pll{(ra * b % mod + rb * a % mod) % mod, (rb * b % mod - ra * a % mod + mod) % mod};
        tie(a, b) = pll{2 * a * b % mod, (b * b % mod - a * a % mod + mod) % mod};
        n >>= 1;
    }

    return {ra, rb};
}