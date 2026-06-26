namespace Poly { // FFT
template <typename real_t>
void fft(vector<complex<real_t> > &a) {
    using cpx = complex<real_t>;
    int n = a.size(), L = __lg(n);
    static vector<complex<long double> > R(2, 1);
    static vector<cpx> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i = k; i < 2 * k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                auto x = (real_t *)&rt[j+k], y = (real_t *)&a[i+j+k];
                cpx z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
                // cpx z = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}
template <typename real_t>
void ifft(vector<complex<real_t> > &a) {
    reverse(a.begin() + 1, a.end());
    fft(a);
    for (auto &e : a) e /= real_t(a.size());
}
template <typename real_t, typename T>
vector<ll> multiply(const vector<T> &A, const vector<T> &B) {
    assert(!A.empty() && !B.empty());
    using cpx = complex<real_t>;
    int need = A.size() + B.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    vector<cpx> in(n), out(n);
    for (int i = 0; i < A.size(); i++) in[i] = A[i];
    for (int i = 0; i < B.size(); i++) in[i].imag(B[i]);
    fft(in);
    for (auto &x : in) x *= x;
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
    vector<ll> res(need);
    for (int i = 0; i < res.size(); i++) res[i] = llround(imag(out[i]) / (4 * n));
	return res;
}
}

namespace Poly { // 정확도 높은 FFT
template <typename real_t>
void fftPrecisely(vector<complex<real_t> > &a, bool inv) {
    using cpx = complex<real_t>;
    int n = a.size(), L = __lg(n);
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] | ((i & 1) << L)) >> 1;
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    vector<cpx> roots(n / 2);
    real_t ang = 2 * acos(real_t(-1)) / n * (inv ? -1 : 1);
    for (int i = 0; i < n / 2; i++) roots[i] = cpx(cos(ang * i), sin(ang * i));
    for (int m = 2; m <= n; m <<= 1) {
        int step = n / m;
        for (int i = 0; i < n; i += m) {
            for (int j = 0; j < m / 2; j++) {
                cpx even = a[i + j];
                cpx odd = roots[step * j] * a[i + j + m / 2];
                a[i + j] = even + odd;
                a[i + j + m / 2] = even - odd;
            }
        }
    }
    if (inv) for (auto &e : a) e /= cpx(n);
}
static constexpr int SPLIT_BIT = 15;
static constexpr ll SPLIT_BASE = 1LL << SPLIT_BIT;
static constexpr ll SPLIT_BASE_SQ = 1LL << SPLIT_BIT * 2;
static constexpr int SPLIT_MASK = (1 << SPLIT_BIT) - 1;
template <typename real_t=double, typename T>
vector<ll> multiplyPrecisely(const vector<T> &A, const vector<T> &B) {
    assert(!A.empty() && !B.empty());
    using cpx = complex<real_t>;
    int need = A.size() + B.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    vector<cpx> a(n), b(n), c1(n), c2(n);
    // for (int i = 0; i < A.size(); i++) a[i] = cpx(A[i] >> SPLIT_BIT, A[i] & SPLIT_MASK); // A[i],B[i]>0
    // for (int i = 0; i < B.size(); i++) b[i] = cpx(B[i] >> SPLIT_BIT, B[i] & SPLIT_MASK);
    for (int i = 0; i < A.size(); i++) a[i] = cpx(A[i] / SPLIT_BASE, A[i] % SPLIT_BASE);
    for (int i = 0; i < B.size(); i++) b[i] = cpx(B[i] / SPLIT_BASE, B[i] % SPLIT_BASE);
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
    vector<ll> res(need);
    for (int i = 0; i < res.size(); i++) {
        ll av = llround(c1[i].real());
        ll bv = llround(c1[i].imag()) + llround(c2[i].real());
        ll cv = llround(c2[i].imag());
        // res[i] = (av << (SPLIT_BIT * 2)) + (bv << SPLIT_BIT) + cv; // av,bv,cv>0
        res[i] = av * SPLIT_BASE_SQ + bv * SPLIT_BASE + cv;
    }
    return res;
}
}
// multiply<double_t>(f, g) : fft 다항식 곱셈 O(N logN)
// multiplyPrecisely<double_t>(f, g) : 정확도 높은 fft 다항식 곱셈 O(N logN)
