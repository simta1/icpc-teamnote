template <typename T>
ld lvs(vector<Point<T>> ps) {
	auto f = [&](Point<T> p) {
		return ld(p.x) * p.x + ld(p.y) * p.y;
	};

	auto v = ps;
	for (auto p : ps) v.push_back(p * -1);
	auto half = [&](auto &p) {
		return p.y < 0 || (p.y == 0 && p.x < 0); // PI <= atan2(p) < 2 * PI
	};
	sort(v.begin(), v.end(), [&](auto &a, auto &b) {
		bool ah = half(a), bh = half(b);
		return ah != bh ? ah < bh : cross(a, b) > 0;
	});

	Point<ll> cur(0, 0);
	for (auto p : ps) if (half(p)) cur = cur + p;

	ld res = f(cur);
	for (auto p : v) {
		cur = cur + p;
		res = max(res, f(cur));
	}
	return res;
}
