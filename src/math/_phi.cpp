template <typename T>
T phi(T n) { // O(sqrt(N))
    T res = n;
    for (long long p = 2; p * p <= n; p++) if (n % p == 0) {
        while (n % p == 0) n /= p;
        res = res / p * (p - 1);
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}

ll phi(ll n) { // O(N^{1/4})
    ll res = n;
    for (auto &p : PollardRho::factorize(n)) res = res / p * (p - 1);
    return res;
}

vector<int> getPhi(int n) { // 함수테이블 계산 // O(N) 
    vector<int> phi(n + 1);
    phi[1] = 1;
    vector<int> primes, lpf(n + 1); // least prime factor
    for (ll i = 2; i <= n; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : primes) {
            if (i * p > n) break;
            lpf[i * p] = p;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            else {
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
    return phi;
}