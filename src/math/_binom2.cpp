// nCr (nCr * r의 값을 오버플로우 없이 저장 가능할 때)
// O(r)
ll nCr(int n, int r) {
    ll res = 1;
    for (int i = 1; i <= r; i++) res = res * n-- / i;
    return res;
}

// nCr mod M
// O(n)
auto nCr = [&](int n, int r, ll mod) {
    ll res = 1;
    for (auto p : primes) {
        int cnt = pAdicValuation(n, p) - pAdicValuation(r, p) - pAdicValuation(n - r, p);
        res *= pow(p, cnt, mod);
    }
    return res;
};
// n 미만 소수 O(N / \log{N})개에 대해 p-지수를 구하는데
// p-지수 계산이 O(log_p{N}) < O(log{N})이므로 전체 O(N)

// iCj mod M (forall 1<=i<=n, 1<=b<=r)
// O(nr)
vector nCr(n + 1, vector<ll>(r + 1));
nCr[1][0] = nCr[1][1] = 1;
for (int i = 2; i <= n; i++) {
    nCr[i][0] = 1;
    for (int j = 1; j <= min(r, i); j++) nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % mod;
}

// nCr mod P
// 전처리 O(N + log{P}), 쿼리 O(1)
vector<ll> fac(n + 1, 1);
for (int i = 2; i < fac.size(); i++) fac[i] = fac[i - 1] * i % mod;
vector<ll> ifac(fac.size(), modInverse(fac.back(), mod));
for (int i = ifac.size() - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i % mod;
auto nCr = [&](int n, int r) {
    return fac[n] * ifac[r] % mod * ifac[n - r] % mod;
};

// nCr mod P (p << n)
// 전처리 O(p), 쿼리 O(log_P{N})
vector<ll> fac(mod, 1);
for (int i = 2; i < mod; i++) fac[i] = fac[i - 1] * i % mod;
vector<ll> ifac(fac.size(), modInverse(fac.back(), mod));
for (int i = ifac.size() - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i % mod;
auto _nCr = [&](int n, int r) -> ll { // n < mod, r < mod
    return fac[n] * ifac[r] % mod * ifac[n - r] % mod;
};
auto nCr = [&](ll n, ll r) -> ll {
    ll res = 1;
    for (; n > 0; n /= mod, r /= mod) {
        if (n % mod < r % mod) return 0;
        res = res * _nCr(n % mod, r % mod) % mod;
    }
    return res;
};

// nCr mod p^e
// 전처리 O(p^e), 쿼리 O(log_P{N} * logN + log(p^e))
vector<int> pFreeFac(mod, 1); // pFreeFac[n] : 1,..., n 중 p와 서로소인 것들을 곱한 값
for (int i = 2; i < mod; i++) pFreeFac[i] = i % p == 0 ? pFreeFac[i - 1] : pFreeFac[i - 1] * i % mod;
auto pReducedFac = [&](auto &&pReducedFac, int n) -> int {
    return n == 0 ? 1 : pow(pFreeFac[mod - 1], n / mod, mod) * pFreeFac[n % mod] % mod * pReducedFac(pReducedFac, n / p) % mod;
};
auto nCr = [&](int n, int r) -> int {
    int pAdic = pAdicValuation(n, p) - pAdicValuation(r, p) - pAdicValuation(n - r, p);
    return pReducedFac(n)
        * modInverse(pReducedFac(r) * pReducedFac(n - r) % mod, mod) % mod
        * pow(p, pAdic, mod) % mod;
};

// nCr mod (p1^e1 * p2^e2 * ... * pk^ek)
// O(p1^e1 + p2^e2 + ... + pk^ek + k * log(p1^e1 * p2^e2 * ... * pk^ek))
// nCr mod p^e 계산후 CRT로 합치면 됨