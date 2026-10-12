template <typename T>
int PIP(const Point<T> &p, const vector<Point<T>> &g) { // -1 : 내부, 0 : 경계, 1 : 외부
	int n = g.size();
	assert(n >= 3);
	bool inside = false;
	auto isBetween = [](T a, T b, T c) { return min(a, c) <= b && b <= max(a, c); };
	for (int i = 0, j = n - 1; i < n; j = i++) {
		const auto &p1 = g[i];
		const auto &p2 = g[j];
		// 다각형 경계
		if (ccw(p1, p, p2) == 0 && isBetween(p1.x, p.x, p2.x) && isBetween(p1.y, p.y, p2.y)) return 0;
		// 다각형 내부
		if (min(p1.y, p2.y) <= p.y && p.y < max(p1.y, p2.y)) {
			if (p1.y < p2.y) inside ^= ccw(p1, p2, p) < 0;
			else inside ^= ccw(p2, p1, p) < 0;
		}
	}
	return 1 - 2 * inside;
}