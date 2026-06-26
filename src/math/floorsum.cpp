ll f(int p, int q, int n) { // p/q + 2p/q + ... + np/q // O(log(min(p, q)))
	assert(q != 0);
	if (p == 0) return 0;
	if (p >= q) return ll(p / q) * n * (n + 1) / 2 + f(p % q, q, n);
	return ll(n) * p / q * n + n / q - f(q, p, ll(p) * n / q);
}
ll floorModSum(int p, int q, int n) { // p % q + 2p % q + ... + np % q // O(log(min(p, q)))
	int g = __gcd(p, q);
	int pg = p / g, qg = q / g;
	return ll(p) * n * (n + 1) / 2 - q * f(pg, qg, n);
}
