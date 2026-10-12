template <typename T>
int PICP(const Point<T> &p, const vector<Point<T>> &h, int dir=0) { // -1 : 내부, 0 : 경계, 1 : 외부 // O(logN)
	int n = h.size();
	assert(n >= 3);
	if (!dir) { // dir은 h에서 점들이 주어진 방향(반시계 : 1, 시계 : -1, 모르는 경우(default) : 0)
		int i = 2;
		while (!dir && i < n) dir = ccw(h[0], h[1], h[i++]);
	}
	assert(dir != 0); // dir = 0이면 모든 점이 일직선 위에 존재
	if (ccw(h[0], h[1], p) * dir < 0) return 1;
	if (ccw(h[0], h[n - 1], p) * dir > 0) return 1;
	if (onPS(p, h[0], h[1])) return 0;
	if (onPS(p, h[0], h[n - 1])) return 0;
	int lo = 1, hi = n;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (ccw(h[0], h[mid], p) * dir >= 0) lo = mid;
		else hi = mid;
	}
	if (hi == n) return 1; // h[0], h[n - 1], p가 일직선인 경우
	return -ccw(h[lo], h[hi], p) * dir;
}
// h에 collinear vertex 없어야됨. 있을땐 테스트안해봄