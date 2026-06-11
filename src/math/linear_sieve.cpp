vector<int> getLpf(int n) {
    vector<int> primes, lpf(n + 1); // least prime factor // O(N)
    for (int i = 2; i <= n; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i > n / p) break;
            lpf[i * p] = p;
            if (i % p == 0) break;
        }
    }
    return lpf;
}