auto clipHL(const vector<Point<ld>> &h, Point<ld> a, Point<ld> b) { // a->b의 왼쪽만 남김
	vector<Point<ld>> res;
	for (int i = 0, j = int(h.size()) - 1; i < h.size(); j = i++) {
		auto p = h[j], q = h[i];
		ld s = cross(b - a, p - a), t = cross(b - a, q - a);
		if (s >= 0) res.push_back(p);
		if ((s < 0 && t > 0) || (s > 0 && t < 0)) res.push_back(p + (q - p) * (s / (s - t)));
	}
	return res;
}
vector<Point<ld>> interHH(vector<Point<ld>> h1, const vector<Point<ld>> &h2) { // O(M(N+M))
	// h2는 반시계여야 됨
	if (h2.empty()) return {};
	for (int i = 0, j = h2.size() - 1; i < h2.size(); j = i++) h1 = clipHL(h1, h2[j], h2[i]);
	return h1;
}
