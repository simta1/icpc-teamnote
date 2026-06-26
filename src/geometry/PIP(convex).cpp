// 헤더: Point, crossProduct, ccw, isBetween, isOnPL
template <typename T>
int PICP(const Point<T> &point, const vector<Point<T> > &polygon, int dir=0) { // -1 : 내부, 0 : 경계, 1 : 외부 // O(logN)
    int n = polygon.size();
    assert(n >= 3);
    if (!dir) { // dir은 polygon에서 점들이 주어진 방향(반시계 : 1, 시계 : -1, 모르는 경우(default) : 0)
        int i = 2;
        while (!dir && i < n) dir = ccw(polygon[0], polygon[1], polygon[i++]);
    }
    assert(dir != 0); // dir = 0이면 모든 점이 일직선 위에 존재
    if (ccw(polygon[0], polygon[1], point) * dir < 0) return 1;
    if (ccw(polygon[0], polygon[n - 1], point) * dir > 0) return 1;
    if (isOnPL(point, polygon[0], polygon[1])) return 0;
    if (isOnPL(point, polygon[0], polygon[n - 1])) return 0;
    int lo = 1, hi = n;
    while (lo + 1 < hi) {
        int mid = lo + hi >> 1;
        if (ccw(polygon[0], polygon[mid], point) * dir >= 0) lo = mid;
        else hi = mid;
    }
    if (hi == n) return 1; // polygon[0], polygon[n - 1], point가 일직선인 경우
    return -ccw(polygon[lo], polygon[hi], point) * dir;
}
// polygon에 collinear vertex 없어야됨. 있을땐 테스트안해봄