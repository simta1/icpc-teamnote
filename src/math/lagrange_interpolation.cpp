ll pm(ll n, ll mod) {
    return (n % mod + mod) % mod;
}
// f(0), ..., f(n) 알고 있을 때 n차 다항식 f(x)의 x좌표에서 함수값 계산
ll lagrangeInterpolation(vector<ll> y, ll x, ll mod) { // O(N \log{MOD})
    assert(!y.empty());
    for (auto &e : y) e = pm(e, mod);
    x = pm(x, mod);
    int n = y.size() - 1;
    if (x <= n) return pm(y[x], mod);
    ll k = 1; // PI_{j!=i} (x - x_j) / (x_i - x_j) 저장
    for (int j = 1; j < y.size(); j++) { // i = 0 // j != i
        k = k * pm(x - j, mod) % mod; // * (x - x_j)
        k = k * modInv(pm(-j, mod), mod) % mod; // / (x_i - x_j)
    }
    ll res = 0;
    for (int i = 0; i <= n; i++) {
        res = (res + y[i] * k) % mod;
        if (i < n) {
            k = k * pm(x - i, mod) % mod * modInv(pm(x - (i + 1), mod), mod) % mod;
            k = k * pm(i - n, mod) % mod * modInv(pm(i + 1, mod), mod) % mod;
        }
    }
    return res;
}
// (x_0, y_0), ..., (x_n, y_n)을 지나는 n차함수:
// y=sum_{i=0}^{n} [ y_i prod_{j \neq i}(x-x_j) / prod_{j \neq i}(x_i-x_j) ]

ll powerSum(ll n, int k, ll mod) { // O(K log{MOD}) + O(K logK) // (1^k + 2^k + ... + n^k) mod M
    vector<ll> y(k + 2, 0);
    for (int x = 1; x <= k + 1; x++) y[x] = (y[x - 1] + power(x, k, mod)) % mod;
    return n < y.size() ? y[n] : lagrangeInterpolation(y, n, mod);
}