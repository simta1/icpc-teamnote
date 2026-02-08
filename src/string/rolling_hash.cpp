template<ll MOD=1'000'000'007>
struct Hashing {
    vector<ll> h;
    static const ll X;
    static vector<ll> x;
    template <typename T> // T = string or vector<>
    Hashing(const T &st) : h(st.size() + 1) {
        while (x.size() <= st.size()) x.push_back(x.back() * X % MOD);
        for (int i = 1; i < h.size(); i++) h[i] = (h[i - 1] * X + st[i - 1]) % MOD; 
    }
    ll get(int s, int e) const { // 0-based, st[s:e)
        ll res = (h[e] - h[s] * x[e - s]) % MOD; // h는 1-based
        return res >= 0 ? res : res + MOD;
    }
};
template<ll MOD> const ll Hashing<MOD>::X = sqrt(MOD) - (__TIME__[6] & 15) * 10 - (__TIME__[7] & 15);
template<ll MOD> vector<ll> Hashing<MOD>::x = {1};
// 2D
template<ll MOD=1'000'000'007>
struct Hashing2D {
    vector<vector<ll> > h;
    static const ll X, Y;
    static vector<ll> x, y;
    template <typename T> // T = string or vector<>
    Hashing2D(const vector<T> &v) {
        int n = v.size();
        int m = v[0].size();
        while (x.size() <= n) x.push_back(x.back() * X % MOD);
        while (y.size() <= m) y.push_back(y.back() * Y % MOD);
        h.assign(n + 1, vector<ll>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                h[i][j] = v[i - 1][j - 1]
                        + h[i - 1][j] * X % MOD
                        + h[i][j - 1] * Y % MOD
                        - h[i - 1][j - 1] * X % MOD * Y % MOD;
                h[i][j] %= MOD;
                if (h[i][j] < MOD) h[i][j] += MOD;
            }
        }
    }
    ll get(int i1, int i2, int j1, int j2) const { // 0-based, v[i1:i2)[j1:j2)
        ll res = h[i2][j2]
               - h[i1][j2] * x[i2 - i1] % MOD
               - h[i2][j1] * y[j2 - j1] % MOD
               + h[i1][j1] * x[i2 - i1] % MOD * y[j2 - j1] % MOD;
        res %= MOD;
        return res >= 0 ? res : res + MOD;
    }
};
template<ll MOD> const ll Hashing2D<MOD>::X = sqrt(MOD) - (__TIME__[6] & 15) * 10 - (__TIME__[7] & 15);
template<ll MOD> const ll Hashing2D<MOD>::Y = sqrt(MOD) + (__TIME__[6] & 15) * 10 + (__TIME__[7] & 15);
template<ll MOD> vector<ll> Hashing2D<MOD>::x = {1};
template<ll MOD> vector<ll> Hashing2D<MOD>::y = {1};
