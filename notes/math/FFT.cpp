namespace Poly { // FFT
    using ll = long long;
    int pow2GE(int n) { return 1 << __lg(n) + !!(n & (n - 1)); }

    vector<vector<pair<int, int> > > bitRev; // 비트 반전 저장 // 다항식 곱셈 한 번에도 fft()가 여러 번 호출되므로 비트 반전 결과를 캐싱해두고 사용하면 성능향상에 좋음
    const vector<pair<int, int> >& getBitRev(int n) {
        if (__lg(n) >= bitRev.size()) bitRev.resize(__lg(n) + 1);

        auto &res = bitRev[__lg(n)];
        if (!res.empty()) return res;
        
        res.reserve(n / 2);
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j >= bit; bit >>= 1) j -= bit;
            j += bit;
            if (i < j) res.emplace_back(i, j);
        }
        return res;
    }

    template <typename T>
    void __transform(vector<T> &f, bool inv, T root) {
        int n = f.size();
        for (auto [i, j] : getBitRev(n)) swap(f[i], f[j]);
        
        if (inv) root = T(1) / root;
        vector<T> wms;
        for (int m = n; m >= 2; m >>=1) {
            wms.push_back(root);
            root *= root;
        }

        for (int m = 2, wIdx = wms.size(); m <= n; m <<= 1) {
            T w_m = wms[--wIdx];
            for (int i = 0; i < n; i += m) {
                T w_j(1); // (w_m)^j
                for (int j = 0; j < m / 2; j++, w_j *= w_m) {
                    T even = f[i + j];
                    T odd = w_j * f[i + j + m / 2];
                    f[i + j] = even + odd;
                    f[i + j + m / 2] = even - odd;
                }
            }
        }

        if (inv) for (auto &e : f) e /= T(n);
    }
    
    template <typename double_t>
    void fft(vector<complex<double_t> > &f, bool inv) {
        double_t t = 2 * acos(double_t(-1)) / f.size(); // acos(double_t(-1))는 PI
        __transform(f, inv, complex<double_t>(cos(t), sin(t)));
    }

    template <typename double_t, typename T>
    vector<ll> multiply(const vector<T> &f, const vector<T> &g) {
        assert(!f.empty() && !g.empty());
        using cpx = complex<double_t>;
        vector<cpx> a(f.begin(), f.end());
        vector<cpx> b(g.begin(), g.end());
        int n = pow2GE(a.size() + b.size() - 1);
        a.resize(n);
        b.resize(n);
        fft(a, false);
        fft(b, false);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        fft(a, true);

        vector<ll> res(f.size() + g.size() - 1);
        for (int i = 0; i < res.size(); i++) res[i] = round(a[i].real());
        return res;
    }
}

namespace Poly { // 정확도 높은 FFT
    template <typename double_t>
    void fftPrecisely(vector<complex<double_t> > &f, bool inv) {
        using cpx = complex<double_t>;
        int n = f.size();
        for (auto [i, j] : getBitRev(n)) swap(f[i], f[j]);
        
        vector<cpx> roots(n / 2);
        double_t ang = 2 * acos(-1) / n * (inv ? -1 : 1);
        for (int i = 0; i < n / 2; i++) roots[i] = cpx(cos(ang * i), sin(ang * i));

        for (int m = 2; m <= n; m <<= 1) {
            int step = n / m;
            for (int i = 0; i < n; i += m) {
                for (int j = 0; j < m / 2; j++) {
                    cpx even = f[i + j];
                    cpx odd = roots[step * j] * f[i + j + m / 2];
                    f[i + j] = even + odd;
                    f[i + j + m / 2] = even - odd;
                }
            }
        }

        if (inv) for (auto &e : f) e /= cpx(n);
	}
    
    static constexpr int splitBit = 15;
    static constexpr int split = (1 << splitBit) - 1;
    template <typename double_t=double, typename T>
    vector<ll> multiplyPrecisely(const vector<T> &v1, const vector<T> &v2) {
        assert(!v1.empty() && !v2.empty());
        using cpx = complex<double_t>;
        int n = pow2GE(v1.size() + v2.size() - 1);
        vector<cpx> a(n), b(n), c1(n), c2(n);
        for (int i = 0; i < v1.size(); i++) a[i] = cpx(v1[i] >> splitBit, v1[i] & split);
        for (int i = 0; i < v2.size(); i++) b[i] = cpx(v2[i] >> splitBit, v2[i] & split);
        fftPrecisely(a, false);
        fftPrecisely(b, false);
        for (int i = 0; i < n; i++) {
            int j = (i ? (n - i) : i);
            cpx ans1 = (a[i] + conj(a[j])) * cpx(0.5, 0);
            cpx ans2 = (a[i] - conj(a[j])) * cpx(0, -0.5);
            cpx ans3 = (b[i] + conj(b[j])) * cpx(0.5, 0);
            cpx ans4 = (b[i] - conj(b[j])) * cpx(0, -0.5);
            c1[i] = (ans1 * ans3) + (ans1 * ans4) * cpx(0, 1);
            c2[i] = (ans2 * ans3) + (ans2 * ans4) * cpx(0, 1);
        }
        fftPrecisely(c1, true);
        fftPrecisely(c2, true);
        
        vector<ll> res(v1.size() + v2.size() - 1);
        for (int i = 0; i < res.size(); i++) {
            ll av = llround(c1[i].real());
            ll bv = llround(c1[i].imag()) + llround(c2[i].real());
			ll cv = llround(c2[i].imag());
            res[i] = (av << 30) + (bv << 15) + cv;
        }
        return res;
    }
}

namespace Poly { // $O(K^2 \log{N})$ 키타마사
    template <typename T>
    vector<ll> divideModNaive(ll n, const vector<T> &g, const ll MOD) { // f(x)=x^n에 대해 f % g 계산 // g 최고차항 계수는 1 // g차수 k일 때 O(K^2 logN)
        const int k = g.size() - 1;
        assert(g[k] == 1);

        vector<ll> res(k), xn(k);
        res[0] = 1;
        if (k == 1) xn[0] = (MOD - g[0]) % MOD; // x === -g[0] (mod x + g[0])
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
        assert(!f.empty() && f[0] != 0); // f(x)의 상수항이 0이면 역원이 존재하지 않음 // 참고로 divideMod(f, g)에서 g의 계수를 뒤집은 게 invertMod의 f이므로 f[0]!=0이란 건 divideMod에서 g의 최고차항의 계수가 0이 아니란 것과 동치임

        vector<ll> res = {mint<p>(f[0]).inv().value}; // f(x)^-1 mod x^1

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
        if (n < m) return {vector<ll>{0}, vector<ll>(f.begin(), f.end())};

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
        if (n <= a.size()) return a[n - 1];

        vector<ll> f(coef.size() + 1, 1); // x^k - c_1 x^(k-1) - c_2 x^(k-2) - ... - c_k x^0
        for (int i = 0; i < coef.size(); i++) f[coef.size() - 1 - i] = -coef[i];
        auto d = divideMod<p, primitiveRoot>(n - 1, f); // x^(n-1)을 {x^k - c_1 x^(k-1) - c_2 x^(k-2) - ... - c_k x^0}로 나눈 나머지

        ll res = 0; // an = a1 * d1 + a2 * d2 + ... + ak * dk
        for (int i = 0; i < d.size(); i++) res = (res + a[i] * d[i]) % p;
        return res;
    }
}

namespace Poly { // multipoint evaluation
    template <ll p, ll primitiveRoot, typename T>
    vector<ll> multiEval(const vector<T> &f, const vector<T> &qs) { // O(NlogN + qlog^q)
        if (qs.empty()) return {};
        assert(!f.empty());
        vector<vector<ll> > tree(4 * qs.size());
        auto build = [&](auto &&build, int node, int s, int e) {
            if (s == e) {
                tree[node] = {(p - qs[s] % p) % p, 1};
                return;
            }
            int m = s + e >> 1;
            build(build, node << 1, s, m);
            build(build, node << 1 | 1, m + 1, e);
            tree[node] = multiplyMod<p, primitiveRoot>(tree[node << 1], tree[node << 1 | 1]);
        };
        build(build, 1, 0, qs.size() - 1); // O(qlog^2q)

        vector<ll> res(qs.size());
        auto eval = [&](auto &&eval, vector<ll> poly, int node, int s, int e) {
            poly = remainderMod<p, primitiveRoot>(poly, tree[node]);
            if (s == e) {
                assert(!poly.empty());
                res[s] = poly[0];
                return;
            }
            int m = s + e >> 1;
            eval(eval, poly, node << 1, s, m);
            eval(eval, poly, node << 1 | 1, m + 1, e);
        };
        eval(eval, f, 1, 0, qs.size() - 1);
        return res;
    }
}
/*
multiply<double_t>(f, g) : fft 다항식 곱셈 O(N logN)
multiplyPrecisely<double_t>(f, g) : 정확도 높은 fft 다항식 곱셈 O(N logN)
multiplyMod<p, primitiveRoot>(f, g) : ntt 다항식 곱셈 O(N logN)
invertMod<p, primitiveRoot>(f, deg) : $f(x)^{-1} \pmod{x^\text{deg}}$ 계산 | $O(N \log{N})$ |
divideMod<p, primitiveRoot>(f, g)  {$f(x) \text{ / } g(x)$, $f(x) \text{ \% } g(x)$} 계산 | $O(N \log{N})$ |
divideMod<p, primitiveRoot>(n, g)  $x^n \pmod{g(x)}$ 계산 | $O(K \log{K} \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
divideModNaive(n, g, MOD)  $x^n \pmod{g(x)}$ 계산 | $O(K^2 \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
kitamasaNTT<p, primitiveRoot>(n, a, coef)  초항 ${a_1, ..., a_k}$과 점화식 $a_i = c_1 a_{i−1} + ... + c_k a_{i−k}$에 대해 $a_n \mod{p}$ 계산 | $O(K \log{K} \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
kitamasaNaive(n, a, coef, MOD)  초항 ${a_1, ..., a_k}$과 점화식 $a_i = c_1 a_{i−1} + ... + c_k a_{i−k}$에 대해 $a_n \mod{\text{MOD}}$ 계산 | $O(K^2 \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
*/

// 미리 계산된 root를 제곱해가며 roots를 얻는 것보다 직접 angle * i의 값에 cos, sin함수를 취해 roots배열을 계산하는 것이 더 정확도가 높음
// 정확도 높음
vector<cpx> roots(n / 2);
double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
for (int i = 0; i < n / 2; i++) roots[i] = cpx(cos(ang * i), sin(ang * i));

// 정확도 낮음
double t = 2 * acos(double_t(-1)) / n * (inv ? -1 : 1);
cpx root(cos(t), sin(t));
vector<cpx> my_roots(n / 2, 1);
for (int i = 1; i < n / 2; i++) my_roots[i] = my_roots[i - 1] * root;