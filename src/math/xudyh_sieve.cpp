template <typename T, T MOD>
class Xudyh {
    vector<T> pfsF; // precomputation
    map<ll, T> mp; // memoization
    T positiveMod(T x) {
        return (x % MOD + MOD) % MOD;
    }
    T pfs_fg(ll x) { // (f * g)(x) = 
        // x %= MOD;
        // return positiveMod();
    };
    T pfs_g(ll x) { // g(x) = 
        // x %= MOD;
        // return positiveMod();
    };
    T pfs_f(ll x) { // f(x) = 
        if (x < pfsF.size()) return pfsF[x]; // precomputation
        if (mp.count(x)) return mp[x];
        auto &res = mp[x];
        res = pfs_fg(x); // S_f(N) = (  S_f*g(N) - sum {d = 2~N} g(d)S_f(N/d)  ) / g(1)
        for (ll i = 2, j; i <= x; i = j + 1) {
            j = x / (x / i);
            res -= pfs_f(x / i) * (pfs_g(j) - pfs_g(i - 1) + MOD) % MOD;
            res %= MOD;
        }
        res = (res + MOD) % MOD;
        res = res * modInv(g(1), MOD) % MOD; // res /= g(1)
        return res;
    }
public:
    Xudyh(ll maxN) {
        int preComputeSize = pow(2.0L * maxN, 2.0L / 3);
        pfsF = getMulFunc(preComputeSize);
        for (int i = 1; i < pfsF.size(); i++) pfsF[i] = (pfsF[i] + pfsF[i - 1]) % MOD;
    }
    T getSum(ll i, ll j) { // O(N^{2/3}) // precomputation 안 할 경우 O(N^{3/4}) // precomputation K까지했을 때 O(K + \dfrac{2N}{\sqrt{K}})
        return positiveMod(pfs_f(j) - pfs_f(i - 1));
    }
};
// g(1)S_f(N) = S_{f*g}(N) - sum_{d=2}^{N} g(d) S_f(N/d))$
// $S_f(N) = (S_{f*g}(N) - sum_{d=2}^{N} g(d) S_f(N/d)) ) / g(1)