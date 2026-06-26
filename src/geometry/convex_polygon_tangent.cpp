// 헤더: Point, crossProduct, ccw, isBetween
template <typename T>
pair<int, int> polygonTangent(const Point<T> &point, const vector<Point<T> > &polygon) { // O(logN)
    // polygon이 반시계 방향 정렬되어있어야함
    int n = polygon.size();
    assert(n >= 3);
    auto _polygonTangent = [&](int up) {
        auto isTangent = [&point, &up](const Point<T> &a, const Point<T> &b, const Point<T> &c) {
            return up * (ccw(point, b, a)) >= 0 && up * (ccw(point, b, c)) >= 0;
        };
        int lo = 0, hi = n;
        if (isTangent(polygon.back(), polygon[0], polygon[1])) return 0;
        while (lo + 1 < hi) {
            int mid = lo + hi >> 1;
            if (isTangent(polygon[mid - 1], polygon[mid], polygon[(mid + 1) % n])) return mid;
            if (up * ccw(point, polygon[lo], polygon[lo + 1]) < 0) { // up
                if (up * ccw(point, polygon[mid], polygon[(mid + 1) % n]) > 0) hi = mid;
                else if (up * ccw(point, polygon[mid], polygon[lo]) > 0) lo = mid;
                else hi = mid;
            }
            else { // down
                if (up * ccw(point,polygon[mid], polygon[(mid + 1) % n]) < 0) lo = mid;
                else if (up * ccw(point, polygon[mid], polygon[lo]) < 0) lo = mid;
                else hi = mid;
            }
        }
        if (lo && isTangent(polygon[lo - 1], polygon[lo], polygon[lo + 1])) return lo;
        if (hi < n && isTangent(polygon[hi - 1], polygon[hi], polygon[(hi + 1) % n])) return hi;
        return -1;
    };
    int a = _polygonTangent(1);
    if (!~a) return {-1, -1}; // 다각형 내부
    vector<int> candi;
    for (int i = 1; i < n && ccw(point, polygon[a], polygon[(a - i + n) % n]) == 0; i++) candi.push_back((a - i + n) % n);
    for (int i = 1; i < n && ccw(point, polygon[a], polygon[(a + i) % n]) == 0; i++) candi.push_back((a + i) % n);
    for (auto e : candi) if (isBetween(point, polygon[e], polygon[a])) a = e;
    int b = _polygonTangent(-1);
    assert (~b);
    candi.clear();
    for (int i = 1; i < n && ccw(point, polygon[b], polygon[(b - i + n) % n]) == 0; i++) candi.push_back((b - i + n) % n);
    for (int i = 1; i < n && ccw(point, polygon[b], polygon[(b + i) % n]) == 0; i++) candi.push_back((b + i) % n);
    for (auto e : candi) if (isBetween(point, polygon[e], polygon[b])) b = e;
    return {a, b};
}

// PICP 대용으로 쓸수있음
// auto [a, b] = polygonTangent(point, polygon);
// if (a == -1) // 내부
// else if (ccw(polygon[a], polygon[b], point) == 0) // 경계
// else // 외부

// collinear points많으면 O(N)으로 늘어날 수 있으니 제거하고 사용