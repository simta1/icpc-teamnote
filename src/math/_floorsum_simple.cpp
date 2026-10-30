ll f(int p, int q, int n) { // gcd(p,q)=1
	assert(q != 0);
	if (p == 0) return 0;
	if (p >= q) return n * ll(n + 1) / 2 * ll(p / q) + f(p % q, q, n);
	return ll(n) * p / q * n + n / q - f(q, p, ll(p) * n / q);
}
ll floorsum(int p, int q, int n) { // p/q + 2p/q + ... + np/q // O(log(min(p, q)))
	int g = gcd(p, q);
	return f(p / g, q / g, n);
}
ll floorModSum(int p, int q, int n) { // p % q + 2p % q + ... + np % q // O(log(min(p, q)))
	int g = __gcd(p, q);
	int pg = p / g, qg = q / g;
	return n * ll(n + 1) / 2 * p - f(pg, qg, n) * q;
}
