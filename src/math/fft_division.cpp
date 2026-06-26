namespace Poly { // $O(K^2 \log{N})$ 키타마사
template <typename T>
vector<ll> divideModNaive(ll n, const vector<T> &g, const ll MOD) { // f(x)=x^n에 대해 f % g 계산 // g 최고차항 계수는 1 // g차수 k일 때 O(K^2 logN)
    const int k = g.size() - 1;
    assert(g[k] == 1);
    vector<ll> res(k), xn(k);
    res[0] = 1;
    if (k == 1) {
        xn[0] = (MOD - g[0]) % MOD; // x === -g[0] (mod x + g[0])
        if (xn[0] < 0) xn[0] += MOD;
    }
    else xn[1] = 1; // x
    auto add = [&MOD](ll &a, ll b) { a = (a + b) % MOD; };
    auto sub = [&MOD](ll &a, ll b) { a = (a - b) % MOD; if (a < 0) a += MOD; };
    auto mul = [&](vector<ll> &a, const vector<ll> &b) {
        vector<ll> scratch(2 * k - 1);
        for (int i = 0; i < k; i++) if (a[i]) for (int j = 0; j < k; ++j) add(scratch[i + j], a[i] * b[j]); // scratch = a * b
        for (int i = 2 * k - 2; i >= k; i--) if (scratch[i]) for (int j = 1; j <= k; ++j) sub(scratch[i - j], scratch[i] * g[k - j]); // scratch %= g
        for (int i = 0; i < k; i++) a[i] = scratch[i];
    };
    while (n) {
        if (n & 1) mul(res, xn);
        mul(xn, xn);
        n >>= 1;
    }
    return res;
}
template <typename T>
ll kitamasaNaive(ll n, const vector<T> &a, const vector<T> &coef, const ll MOD) { // a는 초항{a1, a2, ..., ak}, c는 계수{c1, c2, ..., ck} // A_n = (C_1 x A_n−1 + C_2 x A_n−2 + ... + C_k x A_n−k) mod M일 때 A_n 계산
    assert(n >= 1 && !coef.empty() && a.size() == coef.size());
    if (n <= a.size()) return (a[n - 1] % MOD + MOD) % MOD;
    vector<ll> f(coef.size() + 1, 1); // x^k - c_1 x^(k-1) - c_2 x^(k-2) - ... - c_k x^0
    for (int i = 0; i < coef.size(); i++) f[coef.size() - 1 - i] = (MOD - coef[i]) % MOD;
    auto d = divideModNaive(n - 1, f, MOD); // x^(n-1)을 {x^k - c_1 x^(k-1) - c_2 x^(k-2) - ... - c_k x^0}로 나눈 나머지와 같음
    ll res = 0; // an = a1 * d1 + a2 * d2 + ... + ak * dk
    for (int i = 0; i < d.size(); i++) res = (res + a[i] * d[i]) % MOD;
    return res;
}
}

namespace Poly { // NTT 다항식 나눗셈, 키타마사 // $O(K \log{K} \log{N})$ 키타마사
template <ll p, ll primitiveRoot, typename T>
vector<ll> invertMod(const vector<T> &f, int deg) { // f(x)^-1 mod x^deg 계산 // 계수는 mod p로 계산
    assert(!f.empty() && f[0] % p != 0); // f(x)의 상수항이 0이면 역원이 존재하지 않음 // 참고로 divideMod(f, g)에서 g의 계수를 뒤집은 게 invertMod의 f이므로 f[0]!=0이란 건 divideMod에서 g의 최고차항의 계수가 0이 아니란 것과 동치임
    vector<ll> res = {mint<p>(f[0] % p).inv().value}; // f(x)^-1 mod x^1
    for (int curDeg = 1; curDeg < deg; curDeg <<= 1) {
        int nextDeg = curDeg << 1;

        // prod = f(x) * res(x)
        vector<ll> prod = multiplyMod<p, primitiveRoot>(res, vector<ll>(f.begin(), f.begin() + min(int(f.size()), nextDeg)));
        prod.resize(nextDeg);

        // prod = 2 - f(x) * res(x)
        if ((prod[0] -= 2) < 0) prod[0] += p;
        for (int i = 0; i < prod.size(); i++) if (prod[i] != 0) prod[i] = p - prod[i];

        // 새로운 res(x) = res(x) * (2 - f(x) * res(x))
        res = multiplyMod<p, primitiveRoot>(res, prod);
        res.resize(nextDeg);
    }

    res.resize(deg);
    return res;
}

template <ll p, ll primitiveRoot, typename T>
pair<vector<ll>, vector<ll> > divideMod(const vector<T> &f, const vector<T> &g) {
    int n = f.size(), m = g.size();
    if (n < m) {
        vector<ll> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = f[i] % p;
            if (res[i] < 0) res[i] += p;
        }
        return {vector<ll>{0}, res};
    }

    vector<ll> F(f.rbegin(), f.rend());
    vector<ll> G(g.rbegin(), g.rend());

    vector<ll> q = multiplyMod<p, primitiveRoot>(F, invertMod<p, primitiveRoot>(G, n - m + 1));
    q.resize(n - m + 1);
    reverse(q.begin(), q.end());

    // r(x) = f(x) - q(x) * g(x)
    vector<ll> r = multiplyMod<p, primitiveRoot>(q, g);
    r.resize(m - 1);

    for (int i = 0; i < m - 1; i++) {
        r[i] = (f[i] - r[i]) % p;
        if (r[i] < 0) r[i] += p;
    }

    return {q, r};
}

template <ll p, ll primitiveRoot, typename T>
vector<ll> remainderMod(const vector<T> &f, const vector<T> &g) {
    return divideMod<p, primitiveRoot>(f, g).second;
}

template <ll p, ll primitiveRoot, typename T>
vector<ll> divideMod(ll n, const vector<T> &g) { // f(x)=x^n에 대해 f % g 계산 // g차수 k일 때 O(K logK logN)
    vector<ll> res = {1};
    vector<ll> xn = {0, 1};
    while (n) {
        if (n & 1) res = remainderMod<p, primitiveRoot>(multiplyMod<p, primitiveRoot>(res, xn), g);
        xn = remainderMod<p, primitiveRoot>(multiplyMod<p, primitiveRoot>(xn, xn), g);
        n >>= 1;
    }
    return res;
}
template <ll p, ll primitiveRoot, typename T> // p = a * 2^b + 1 꼴 소수
ll kitamasaNTT(ll n, const vector<T> &a, const vector<T> &coef) { // a는 초항{a1, a2, ..., ak}, c는 계수{c1, c2, ..., ck} // A_n = (C_1 x A_n−1 + C_2 x A_n−2 + ... + C_k x A_n−k) mod P일 때 A_n 계산
    assert(n >= 1 && !coef.empty() && a.size() == coef.size());
    if (n <= a.size()) return a[n - 1];
    vector<ll> f(coef.size() + 1, 1); // x^k - c_1 x^(k-1) - c_2 x^(k-2) - ... - c_k x^0
    for (int i = 0; i < coef.size(); i++) f[coef.size() - 1 - i] = -coef[i];
    auto d = divideMod<p, primitiveRoot>(n - 1, f); // x^(n-1)을 {x^k - c_1 x^(k-1) - c_2 x^(k-2) - ... - c_k x^0}로 나눈 나머지
    ll res = 0; // an = a1 * d1 + a2 * d2 + ... + ak * dk
    for (int i = 0; i < d.size(); i++) res = (res + a[i] * d[i]) % p;
    return res;
}
}
/*
multiplyMod<p, primitiveRoot>(f, g) : ntt 다항식 곱셈 O(N logN)
invertMod<p, primitiveRoot>(f, deg) : $f(x)^{-1} \pmod{x^\text{deg}}$ 계산 | $O(N \log{N})$ |
divideMod<p, primitiveRoot>(f, g)  {$f(x) \text{ / } g(x)$, $f(x) \text{ \% } g(x)$} 계산 | $O(N \log{N})$ |
divideMod<p, primitiveRoot>(n, g)  $x^n \pmod{g(x)}$ 계산 | $O(K \log{K} \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
divideModNaive(n, g, MOD)  $x^n \pmod{g(x)}$ 계산 | $O(K^2 \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
kitamasaNTT<p, primitiveRoot>(n, a, coef)  초항 ${a_1, ..., a_k}$과 점화식 $a_i = c_1 a_{i−1} + ... + c_k a_{i−k}$에 대해 $a_n \mod{p}$ 계산 | $O(K \log{K} \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
kitamasaNaive(n, a, coef, MOD)  초항 ${a_1, ..., a_k}$과 점화식 $a_i = c_1 a_{i−1} + ... + c_k a_{i−k}$에 대해 $a_n \mod{\text{MOD}}$ 계산 | $O(K^2 \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
*/