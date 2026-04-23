[카테고리](/README.md)
## 다항식 연산
### FFT (Fast Fourier Transform)
```cpp
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
    void __transform(vector<T> &f, bool is_reverse, T root) {
        int n = f.size();
        for (auto [i, j] : getBitRev(n)) swap(f[i], f[j]);
        
        if (is_reverse) root = T(1) / root;
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

        if (is_reverse) for (auto &e : f) e /= T(n);
    }
    
    template <typename double_t>
    void fft(vector<complex<double_t> > &f, bool is_reverse) {
        double_t t = 2 * acos(double_t(-1)) / f.size(); // acos(double_t(-1))는 PI
        __transform(f, is_reverse, complex<double_t>(cos(t), sin(t)));
    }

    template <typename double_t, typename T>
    vector<ll> multiply(const vector<T> &f, const vector<T> &g) {
        using cpx = complex<double_t>;
        vector<cpx> a(f.begin(), f.end());
        vector<cpx> b(g.begin(), g.end());
        int n = pow2GE(a.size() + b.size());
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
```
### 정확도 높은 FFT
```cpp
namespace Poly { // 정확도 높은 FFT
    template <typename double_t>
    void fftPrecisely(vector<complex<double_t> > &f, bool is_reverse) {
        using cpx = complex<double_t>;
        int n = f.size();
        for (auto [i, j] : getBitRev(n)) swap(f[i], f[j]);
        
        vector<cpx> roots(n / 2);
		double_t ang = 2 * acos(-1) / n * (is_reverse ? -1 : 1);
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

        if (is_reverse) for (auto &e : f) e /= cpx(n);
	}
    
    static constexpr int splitBit = 15;
    static constexpr int split = (1 << splitBit) - 1;
    template <typename double_t=double, typename T>
    vector<ll> multiplyPrecisely(const vector<T> &v1, const vector<T> &v2) {
        using cpx = complex<double_t>;
        int n = pow2GE(v1.size() + v2.size() + 1);
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
```
### NTT (Number Theoretic Transform) ([ModInt](/utils/ModInt.md) 코드 필요)
```cpp
namespace Poly { // NTT
    template <ll p, ll primitiveRoot>
    void ntt(vector<mint<p> > &f, bool is_reverse) {
        __transform(f, is_reverse, mint<p>(primitiveRoot).pow((p - 1) / f.size()));
    }
    
    // | p = a*2^b+1   | a   | b  | 2^b       | g |
    // | ------------- | --- | -- | --------- | - |
    // | 104'857'601   | 25  | 22 | 4194304   | 3 |
    // | 469,762,049   | 7   | 26 | 8388608   | 3 |
    // | 998'244'353   | 119 | 23 | 8388608   | 3 |
    // | 1,004,535,809 | 479 | 21 | 8388608   | 3 |
    // | 2'281'701'377 | 17  | 27 | 134217728 | 3 |
    // | 2'483'027'969 | 37  | 26 | 67108864  | 3 |
    template <ll p, ll primitiveRoot, typename T> // p = a * 2^b + 1 꼴 소수, n <= 2^b인 n차 다항식에 대해 mod P에서의 다항식 곱셈 계산
    vector<ll> multiplyMod(const vector<T> &f, const vector<T> &g) {
        vector<mint<p> > a(f.begin(), f.end());
        vector<mint<p> > b(g.begin(), g.end());
        int n = pow2GE(a.size() + b.size());
        assert(n <= ((p - 1) & -(p - 1)));
        a.resize(n);
        b.resize(n);
        ntt<p, primitiveRoot>(a, false);
        ntt<p, primitiveRoot>(b, false);
        for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
        ntt<p, primitiveRoot>(a, true);
        
        vector<ll> res(f.size() + g.size() - 1);
        for (int i = 0; i < res.size(); i++) res[i] = a[i].value; // 모든 계수가 0 <= 계수 < MOD를 만족함
        return res;
    }
}
```
### $O(K^2 \log{N})$ 키타마사
```cpp
namespace Poly {
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
```
### 다항식 나눗셈, $O(K \log{K} \log{N})$ 키타마사
```cpp
namespace Poly { // NTT 다항식 나눗셈, 키타마사
    template <ll p, ll primitiveRoot, typename T>
    vector<ll> invertMod(const vector<T> &f, int deg) { // f(x)^-1 mod x^deg 계산 // 계수는 mod p로 계산
        assert(f[0] != 0); // f(x)의 상수항이 0이면 역원이 존재하지 않음 // 참고로 divideMod(f, g)에서 g의 계수를 뒤집은 게 invertMod의 f이므로 f[0]!=0이란 건 divideMod에서 g의 최고차항의 계수가 0이 아니란 것과 동치임

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
```
### 시간복잡도 
| 함수명 | 용도 | 시간복잡도 |
| - | - | - |
| `multiply<double_t>(f, g)` | fft 다항식 곱셈 | $O(N \log{N})$ |
| `multiplyPrecisely<double_t>(f, g)` | 정확도 높은 fft 다항식 곱셈 |  $O(N \log{N})$ |
| `multiplyMod<p, primitiveRoot>(f, g)` | ntt 다항식 곱셈 | $O(N \log{N})$ |
| `invertMod<p, primitiveRoot>(f, deg)` | $f(x)^{-1} \pmod{x^\text{deg}}$ 계산 | $O(N \log{N})$ |
|`divideMod<p, primitiveRoot>(f, g)` | {$f(x) \text{ / } g(x)$, $f(x) \text{ \% } g(x)$} 계산 | $O(N \log{N})$ |
|`divideMod<p, primitiveRoot>(n, g)` | $x^n \pmod{g(x)}$ 계산 | $O(K \log{K} \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
|`divideModNaive(n, g, MOD)` | $x^n \pmod{g(x)}$ 계산 | $O(K^2 \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
|`kitamasaNTT<p, primitiveRoot>(n, a, coef)` | 초항 ${a_1, ..., a_k}$과 점화식 $a_i = c_1 a_{i−1} + ... + c_k a_{i−k}$에 대해 $a_n \mod{p}$ 계산 | $O(K \log{K} \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   
|`kitamasaNaive(n, a, coef, MOD)` | 초항 ${a_1, ..., a_k}$과 점화식 $a_i = c_1 a_{i−1} + ... + c_k a_{i−k}$에 대해 $a_n \mod{\text{MOD}}$ 계산 | $O(K^2 \log{N})$ ($K$는 $g(x)$의 최고차항의 차수)   

`<p, primitiveRoot>`가 붙은 함수는 NTT사용하는 함수임   
kitamasa의 경우 MOD가 NTT를 사용할 수 없는 수라면 `kitamasaNaive(n, g, MOD)`를 써야 함   

### 구현 주의사항
정확도 높은 fft에서는 더 높은 정확도를 위해 `fft()` 함수 대신 `fftPrecisely()`함수를 새로 작성해서 사용했음   
`__transform()`의 구조를 `fftPrecisely()`와 비슷하게 작성하고 매개변수로 `T root` 대신 `vector<T> &roots`를 받도록 하면 코드의 재사용률을 높일 수 있지만 fftPrecisely()의 속도가 생각보다 느려서 따로 사용하기로 결정함   
```cpp
// 정확도 높음
vector<cpx> roots(n / 2);
double ang = 2 * acos(-1) / n * (is_reverse ? -1 : 1);
for (int i = 0; i < n / 2; i++) roots[i] = cpx(cos(ang * i), sin(ang * i));

// 정확도 낮음
double t = 2 * acos(double_t(-1)) / n * (is_reverse ? -1 : 1);
cpx root(cos(t), sin(t));
vector<cpx> my_roots(n / 2, 1);
for (int i = 1; i < n / 2; i++) my_roots[i] = my_roots[i - 1] * root;

// 미리 계산된 root를 제곱해가며 roots를 얻는 것보다 직접 angle * i의 값에 cos, sin함수를 취해 roots배열을 계산하는 것이 더 정확도가 높음
```

### 사용설명
FFT 쓸 때 가능하면 double 사용   
오차범위 확인할 때 참고 -> [부동소수점 오류](https://www.acmicpc.net/blog/view/37)   

```cpp
// FFT를 사용하여 곱셈
// 최대/최소값의 범위가 그리 크지 않다면 double을 사용하는 게 낫다. long double은 정말 느리다.
auto res = Poly::multiply<double>(poly1, poly2);
auto res = Poly::multiply<long double>(poly1, poly2);

// NTT를 사용해 곱셈
auto res = Poly::multiplyMod<998'244'353, 3>(poly1, poly2);
auto res = Poly::multiplyMod<2'281'701'377, 3>(poly1, poly2);
auto res = Poly::multiplyMod<2'483'027'969, 3>(poly1, poly2);

// NTT+CRT
auto res = Poly::multiplyMod5e18(poly1, poly2);
```

### 문제
[큰 수 곱셈 (2)](https://www.acmicpc.net/problem/15576)   
[큰 수 곱셈 (3)](https://www.acmicpc.net/problem/22289)   
[보석 가게](https://www.acmicpc.net/problem/13575)   
[씽크스몰](https://www.acmicpc.net/problem/11385) - NTT + CRT(`multiplyMod5e18()` 함수 사용하면 됨)   
[피보나치 수 3](https://www.acmicpc.net/problem/2749) - $O(K^2 \log{N})$ 키타마사(`kitamasaNaive()`)   
[타일 채우기 2](https://www.acmicpc.net/problem/13976) - $O(K^2 \log{N})$ 키타마사(`kitamasaNaive()`)   
[블록 4](https://www.acmicpc.net/problem/15572) - $O(K^2 \log{N})$ 키타마사(`kitamasaNaive()`)   
[RNG](https://www.acmicpc.net/problem/13725) - NTT 다항식 나눗셈, $O(K \log{K} \log{N})$ 키타마사(`kitamasaNTT()`)   

### 원리
FFT의 비재귀 구현을 위해 `f[i]`와 `f[bitReverse(i)]`를 swap하는 과정에서 비트트릭 사용   
```cpp
// 느린 코드
    int bitReverse(int n, int len) {
        int rev = 0;
        for (int i = 0; i < len; i++) rev |= ((n >> i) & 1) << (len - i - 1);
        return rev;
    }

    void fft(vector<cpx> &f, bool is_reverse) {
        int n = f.size();
        int len = __builtin_ctz(n);
        
        for (int i = 0; i < n; i++) {
            int j = bitReverse(i, len);
            if (i < j) swap(f[i], f[j]);
        }
        // ...
    }

// 빠른코드
    void fft(vector<cpx> &f, bool is_reverse) {
        int n = f.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j >= bit; bit >>= 1) j -= bit;
            j += bit;
            if (i < j) swap(f[i], f[j]);
        }
        // ...
    }
```

> 다항식 나눗셈에서 사용되는 invertMod의 원리([출처](https://algoshitpo.github.io/2020/05/20/fft-ntt/))   
$B(x)C(x) \equiv 1 \pmod{x^k}$   
$B(x)C(x) - 1 \equiv 0 \pmod{x^k}$   
$(B(x)C(x) - 1)^2 \equiv 0 \pmod{x^{2k}}$   
$B(x)^2 C(x)^2 - 2b(x)C(x) + 1 \equiv 0 \pmod{x^{2k}}$   
$B(x)C(x)(2 - B(x)C(x)) \equiv 1 \pmod{x^{2k}}$   
$B(x)^{-1} \equiv C(x)(2-B(x)C(x)) \pmod{x^{2k}}$   
>
> 따라서 $\mod{x^k}$에서 $B(x)$의 역원 $C(x)$를 안다면 $\mod{x^{2k}}$의 역원은 $C(x) (2 - B(x)C(x))$로 계산할 수 있다.   

### 참고링크
https://algoshitpo.github.io/2020/05/20/fft-ntt/ - fft, 정확도 높은 fft, ntt, 키타마사   
https://algoshitpo.github.io/2020/05/20/linear-recurrence/ - 다항식 나눗셈   
https://blog.myungwoo.kr/147 - 다항식 나눗셈 시간복잡도   
https://hyperbolic.tistory.com/4 - 다항식 나눗셈   
https://justicehui.github.io/hard-algorithm/2021/03/13/kitamasa/ - 키타마사   
https://blog.myungwoo.kr/148 - 키타마사   