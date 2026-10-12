template <typename T, typename F>
int extremeVertex(const vector<Point<T>> &h, F direction) {
	// 공선점 없어야됨, h반시계
	int n = h.size();
	assert(n >= 3);
	auto cmp = [&](int i, int j) {
		T v = cross(direction(h[j]), h[j] - h[i]);
		return (v > 0) - (v < 0);
	};
	auto slope = [&](int i) {
		return cmp((i + 1) % n, i);
	};
	auto check = [&](int i) {
		return slope(i) >= 0 && cmp(i, (i + n - 1) % n) < 0;
	};
	int l = 0, r = check(0) ? 1 : n;
	int s = slope(0);
	while (l + 1 < r) {
		int m = (l + r) / 2, t = slope(m);
		if (check(m)) return m;
		if (s != t ? s < t : s == cmp(l, m)) r = m;
		else l = m, s = t;
	}
	return l;
}
// 다각형의 모든 꼭짓점이 "p를 지나며 direction(p)방향의 직선"  오른쪽에 놓이게 되는 p의 인덱스 리턴
// 즉, cross(direction(p), h[i]-p)<=0
// 접선이 다각형의 변과 접하는 경우, 그 변에서 ccw순서상 첫번째점이 반환됨

auto tangent = [&](Point<T> p, const vector<Point<T>> &h) {
	// p가 h에 대해 strictly outside여야됨
	int a = extremeVertex(h, [&](Point<T> q) { return q - p; });
	int b = extremeVertex(h, [&](Point<T> q) { return p - q; });
	return pair{a, b};
};
int i = extremeVertex(h, [&](Point<T> q) { return dir; });
