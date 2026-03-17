vector<int> getMoebius(int n) { // O(N)
    vector<int> mu(n + 1);
    mu[1] = 1;
    vector<int> primes, lpf(n + 1); // least prime factor
    for (ll i = 2; i <= n; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (auto p : primes) {
            if (i * p > n) break;
            lpf[i * p] = p;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            else {
                mu[i * p] = mu[i] * mu[p];
            }
        }
    }
    return mu;
}

vector<int> getMoebius(int n) { // O(NloglogN)
    vector<int> mu(n + 1);
    mu[1] = 1;
    for (int i = 1; i <= n; i++) if (mu[i]) {
        for (int j = i * 2; j <= n; j += i) mu[j] -= mu[i];
    }
    return mu;
}