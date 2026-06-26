// 헤더: Point, crossProduct, ccw
template <typename T>
int PIP(const Point<T> &point, const vector<Point<T> > &polygon) { // -1 : 내부, 0 : 경계, 1 : 외부
    int n = polygon.size();
    assert(n >= 3);
    bool inside = false;
    auto isBetween = [](T a, T b, T c) { return min(a, c) <= b && b <= max(a, c); };
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const auto &p1 = polygon[i];
        const auto &p2 = polygon[j];
        // 다각형 경계
        if (ccw(p1, point, p2) == 0 && isBetween(p1.x, point.x, p2.x) && isBetween(p1.y, point.y, p2.y)) return 0;
        // 다각형 내부
        if (min(p1.y, p2.y) <= point.y && point.y < max(p1.y, p2.y)) {
            if (p1.y < p2.y) inside ^= ccw(p1, p2, point) < 0;
            else inside ^= ccw(p2, p1, point) < 0;
        }
    }
    return 1 - 2 * inside;
}