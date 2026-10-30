// sum_{x=0}^{n-1}floor((ax+b)/m) // O(logM)
// 0 <= n < 2^32, 1 <= m < 2^32, a, b >= 0
ull floorsum_unsigned(ull n, ull m, ull a, ull b) {
	ull ans = 0;
	while (1) {
		if (a >= m) {
			ans += n * (n - 1) / 2 * (a / m);
			a %= m;
		}
		if (b >= m) {
			ans += n * (b / m);
			b %= m;
		}
		ull y = a * n + b;
		if (y < m) break;
		n = y / m;
		b = y % m;
		swap(a, m);
	}
	return ans;
}
// 0 <= n < 2^32, 1 <= m < 2^32
ll floorsum(ll n, ll m, ll a, ll b) {
	ull ans = 0;
	if (a < 0) {
		ull a2 = (a % m + m) % m;
		ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
		a = a2;
	}
	if (b < 0) {
		ull b2 = (b % m + m) % m;
		ans -= 1ULL * n * ((b2 - b) / m);
		b = b2;
	}
	return ans + floorsum_unsigned(n, m, a, b);
}
