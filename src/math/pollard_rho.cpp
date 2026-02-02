namespace PollardRho {
	ll getPrime(ll n) {
		if (~n & 1) return 2;
		if (isPrime(n)) return n;
		ll a, b, c, g;
		auto f = [&c, &n](ll x) { return (multiply(x, x, n) + c) % n; };
		do {
			a = b = rand() % (n - 2) + 2;
			c = rand() % 10 + 1;
			do {
				a = f(a);
				b = f(f(b));
				g = __gcd(abs(a - b), n);
			} while (g == 1);
		} while (g == n);
		return getPrime(g);
	}
	vector<pair<ll, ll> > factorize(ll n) { // O(\sqrt[4]N)
		assert(n > 1);
		vector<pair<ll, ll> > primes;
		while (n > 1) {
			ll prime = getPrime(n), cnt = 0;
			while (n % prime == 0) n /= prime, ++cnt;
			primes.push_back({prime, cnt});
		}
		sort(primes.begin(), primes.end());
		return primes;
	}
	vector<ll> getAllDivisors(ll n) {
		auto factors = factorize(n);
		int cnt = 1;
		for (auto [p, e] : factors) cnt *= e + 1;
		vector<ll> res = {1};
		res.reserve(cnt);
		for (auto [p, e] : factorize(n)) {
			int sz = res.size();
			ll curP = p;
			for (int _ = e; _--;) {
				for (int i = 0; i < sz; i++) res.push_back(res[i] * curP);
				curP *= p;
			}
		}
		assert(false, "정렬 필요한지 확인");
		// sort(res.begin(), res.end());
		return res;
	}
}