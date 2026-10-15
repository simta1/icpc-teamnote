template <typename T>
int PIP(const Point<T> &p, const vector<Point<T>> &g) { // -1 : 내부, 0 : 경계, 1 : 외부
	int n = g.size(), in = 0;
	assert(n >= 3);
	for (int i = 0, j = n - 1; i < n; j = i++) {
		if (onPS(p, g[i], g[j])) return 0;
		if ((g[i].y > p.y) != (g[j].y > p.y)) in ^= (ccw(g[i], g[j], p) < 0) == (g[i].y < g[j].y);
	}
	return 1 - 2 * in;
}