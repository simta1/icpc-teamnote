// mod <= INT_MAX
ll binpow(ll a, ll n, ll mod) { // a ^ n % mod
	ll res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

using pll = pair<ll, ll>;
pll tanNth(ll a, ll b, ll n, ll mod) { // tanT = a / b, tan(nT) = ?
	a %= mod;
	b %= mod;
	if (a < 0) a += mod;
	if (b < 0) b += mod;
	ll ra = 0, rb = 1;
	for (; n; n >>= 1) {
		if (n & 1) tie(ra, rb) = pll{(ra * b % mod + rb * a % mod) % mod, (rb * b % mod - ra * a % mod + mod) % mod};
		tie(a, b) = pll{2 * a * b % mod, (b * b % mod - a * a % mod + mod) % mod};
	}
	return {ra, rb};
}