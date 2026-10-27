tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
	if (b == 0) return {1, 0, a};
	auto [x, y, g] = egcd(b, a % b);
	return {y, x - (a / b) * y, g};
} // x<=b/g, y<=a/g
ll modInv(ll a, ll b) {
	auto [x, y, g] = egcd(a, b);
	return g != 1 ? -1 : (x + b) % b;
} // modInv(n, MOD)
static ll inv[N + 1] = {1, 1};
for (int i = 2; i <= N; ++i) inv[i] = inv[P % i] * (P - P / i) % P;
