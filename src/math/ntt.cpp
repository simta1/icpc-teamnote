namespace Poly { // NTT
template <ll p> ll binpow(ll a, ll n) { // (MOD-1)^2<=INT64_MAX
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = res * a % p;
        a = a * a % p;
    }
    return res;
}
template <ll p, ll primitiveRoot>
void ntt(vector<ll> &a, bool inv) {
    int n = a.size(), L = __lg(n);
    static vector<ll> rt(2, 1);
    for (static int k = 2, s = 2; k < n; k <<= 1, ++s) {
        rt.resize(n);
        ll z[2] = {1, binpow<p>(primitiveRoot, p >> s)};
        for (int i = k; i < 2 * k; i++) rt[i] = rt[i >> 1] * z[i & 1] % p;
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] | ((i & 1) << L)) >> 1;
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll u = a[i + j], v = a[i + j + k] * rt[j + k] % p;
                a[i + j] = u + v < p ? u + v : u + v - p;
                a[i + j + k] = u - v >= 0 ? u - v : u - v + p;
            }
        }
    }
    if (inv) {
        reverse(a.begin() + 1, a.end());
        ll invN = binpow<p>(n, p - 2);
        for (auto &e : a) e = e * invN % p;
    }
}
template <ll p, ll primitiveRoot, typename T>
vector<ll> multiplyMod(const vector<T> &A, const vector<T> &B) {
    assert(!A.empty() && !B.empty());
    int need = A.size() + B.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    assert(n <= ((p - 1) & -(p - 1))); // assert(n <= 2^b)
    vector<ll> a(n), b(n);
    for (int i = 0; i < A.size(); i++) {
        a[i] = A[i] % p;
        if (a[i] < 0) a[i] += p;
    }
    for (int i = 0; i < B.size(); i++) {
        b[i] = B[i] % p;
        if (b[i] < 0) b[i] += p;
    }
    ntt<p, primitiveRoot>(a, false);
    ntt<p, primitiveRoot>(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % p;
    ntt<p, primitiveRoot>(a, true);
    a.resize(need);
    return a;
}
// | p = a*2^b+1   | a   | b  | 2^b       | g |
// | ------------- | --- | -- | --------- | - |
// | 104'857'601   | 25  | 22 | 4194304   | 3 |
// | 167'772'161   | 5   | 25 | 33554432  | 3 |
// | 469'762'049   | 7   | 26 | 67108864  | 3 |
// | 998'244'353   | 119 | 23 | 8388608   | 3 |
// | 1'004'535'809 | 479 | 21 | 2097152   | 3 |
// | 1'012'924'417 | 483 | 21 | 2097152   | 5 |
// | 2'281'701'377 | 17  | 27 | 134217728 | 3 |
// | 2'483'027'969 | 37  | 26 | 67108864  | 3 |
}
