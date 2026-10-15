template <typename T>
int PICP(const Point<T> &p, const vector<Point<T>> &h) { // -1 : 내부, 0 : 경계, 1 : 외부
	// h : ccw, no collinear
	assert(h.size() >= 3);
	if (int c = ccw(h[0], h[1], p); c <= 0) return c < 0 || dot(p - h[0], p - h[1]) > 0;
	if (int c = ccw(h[0], h.back(), p); c >= 0) return c > 0 || dot(p - h[0], p - h.back()) > 0;
	auto it = upper_bound(h.begin() + 1, h.end(), p, [&](const auto &a, const auto &b) { return ccw(h[0], a, b) > 0; });
	return -ccw(*prev(it), *it, p);
}