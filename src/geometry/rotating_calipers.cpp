template <typename T>
T getDiameterSquare(const vector<Point<T>> &h) { // O(NlogN)
	// h 반시계여야함
	if (h.size() <= 1) return 0;
	if (h.size() == 2) return dist2PP(h[0], h[1]);
	T res = 0;
	int n = h.size(), a = 0, b = 1;
	while (a < n && b < 2 * n) {
		res = max(res, dist2PP(h[a % n], h[b % n]));
		if (cross(h[(a + 1) % n] - h[a % n], h[(b + 1) % n] - h[b % n]) >= 0) ++b;
		else ++a;
	}
	return res;
}
template <typename T>
inline T f(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
	return cross(b - a, c - a);
}
template <typename T>
T largestTriangleDouble(const vector<Point<T>> &h) { // O(N^2) // 볼록껍질에 포함되는 가장 큰 삼각형의 넓이
	assert(h.size() >= 3);
	T res = 0;
	for (int i = 0; i + 2 < h.size(); i++) {
		for (int j = i + 1, k = i + 2; j < h.size(); j++) {
			while (k + 1 < h.size() && f(h[i], h[j], h[k]) < f(h[i], h[j], h[k + 1])) ++k;
			res = max(res, f(h[i], h[j], h[k]));
		}
	}
	return res;
}
