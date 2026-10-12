template <typename T>
bool isBetween(Point<T> a, Point<T> b, Point<T> c) {
	return min(a.x, c.x) <= b.x && b.x <= max(a.x, c.x)
		&& min(a.y, c.y) <= b.y && b.y <= max(a.y, c.y);
}
template <typename T>
pair<int, int> tangent(const Point<T> &p, const vector<Point<T>> &h) { // O(logN)
	// h: 반시계 정렬되어있어야함
	int n = h.size();
	assert(n >= 3);
	auto _polygonTangent = [&](int up) {
		auto isTangent = [&p, &up](const Point<T> &a, const Point<T> &b, const Point<T> &c) {
			return up * (ccw(p, b, a)) >= 0 && up * (ccw(p, b, c)) >= 0;
		};
		int lo = 0, hi = n;
		if (isTangent(h.back(), h[0], h[1])) return 0;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (isTangent(h[mid - 1], h[mid], h[(mid + 1) % n])) return mid;
			if (up * ccw(p, h[lo], h[lo + 1]) < 0) { // up
				if (up * ccw(p, h[mid], h[(mid + 1) % n]) > 0) hi = mid;
				else if (up * ccw(p, h[mid], h[lo]) > 0) lo = mid;
				else hi = mid;
			}
			else { // down
				if (up * ccw(p,h[mid], h[(mid + 1) % n]) < 0) lo = mid;
				else if (up * ccw(p, h[mid], h[lo]) < 0) lo = mid;
				else hi = mid;
			}
		}
		if (lo && isTangent(h[lo - 1], h[lo], h[lo + 1])) return lo;
		if (hi < n && isTangent(h[hi - 1], h[hi], h[(hi + 1) % n])) return hi;
		return -1;
	};
	int a = _polygonTangent(1);
	if (!~a) return {-1, -1}; // 다각형 내부
	vector<int> candi;
	for (int i = 1; i < n && ccw(p, h[a], h[(a - i + n) % n]) == 0; i++) candi.push_back((a - i + n) % n);
	for (int i = 1; i < n && ccw(p, h[a], h[(a + i) % n]) == 0; i++) candi.push_back((a + i) % n);
	for (auto e : candi) if (isBetween(p, h[e], h[a])) a = e;
	int b = _polygonTangent(-1);
	assert (~b);
	candi.clear();
	for (int i = 1; i < n && ccw(p, h[b], h[(b - i + n) % n]) == 0; i++) candi.push_back((b - i + n) % n);
	for (int i = 1; i < n && ccw(p, h[b], h[(b + i) % n]) == 0; i++) candi.push_back((b + i) % n);
	for (auto e : candi) if (isBetween(p, h[e], h[b])) b = e;
	return {a, b};
}

// PICP 대용으로 쓸수있음
// auto [a, b] = tangent(p, h);
// if (a == -1) // 내부
// else if (ccw(h[a], h[b], p) == 0) // 경계
// else // 외부

// collinear points많으면 O(N)으로 늘어날 수 있으니 제거하고 사용