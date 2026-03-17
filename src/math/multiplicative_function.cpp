vector<ll> getMulFunc(int n) { // O(N)
    vector<ll> func(n + 1);
    func[1] = 1;
    vector<int> primes, lpf(n + 1), lpe(n + 1); // least prime factor, least prime exponent
    for (ll i = 2; i <= n; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            lpe[i] = 1;
            primes.push_back(i);
            // func[i] = ? // func(p) // i는 소수
        }
        for (auto p : primes) {
            if (i * p > n) break;
            lpf[i * p] = p;
            if (i % p == 0) {
                lpe[i * p] = lpe[i] + 1;
                // func[i * p] = ? // func(i' * p * p) // 소인수 p의 지수 1 증가
                break;
            }
            else {
                lpe[i * p] = 1;
                func[i * p] = func[i] * func[p]; // gcd(i, p) = 1
            }
        }
    }
    return func;
}