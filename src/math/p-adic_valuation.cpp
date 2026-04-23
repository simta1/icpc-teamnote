template <typename T>
T v_p(T n, T p) { // n!의 p-지수
    T res = 0;
    while (n) res += (n /= p);
    return res;
}

// (n!)/(p^v_p(n)) % (p^e) (p진법에서 n!의 0이 아닌 마지막 e자리)
ll power(ll a, ll n, ll mod) { // a ^ n % mod
    ll res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
ll pReducedFactorial(ll n, int p, int mod) {
    vector<int> pFreeFac(mod, 1);
    for (int i = 2; i < mod; i++) pFreeFac[i] = i % p == 0 ? pFreeFac[i - 1] : pFreeFac[i - 1] * i % mod;
    function<int(int)> f = [&](int n) -> int {
        return n == 0 ? 1 : power(pFreeFac[mod - 1], n / mod, mod) * pFreeFac[n % mod] % mod * f(n / p) % mod;
    };
    return f(n);
} // preprocessing O(p^e), query O(log_p(n) log(n))