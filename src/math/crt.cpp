ll crt(ll a, ll m, ll b, ll n) { // m,n>0, 0<=a<m, 0<=b<n, lcm(m,n)<=LLONG_MAX
	if (n > m) swap(a, b), swap(m, n);
	auto [x, y, g] = egcd(m, n);
	if ((b - a) % g) return -1;
	ll t = (b - a) / g * x % (n / g);
	if (t < 0) t += (n / g);
	return a + m * t;
} // -1 or [0, lcm(m,n))