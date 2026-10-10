// 헤더: Point, cross, ccw, distPP
template <typename T>
Point<ld> circumcircle(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3) {
    Point<T> b = p2 - p1, c = p3 - p1;
    T dist12 = b.x * b.x + b.y * b.y;
    T dist23 = c.x * c.x + c.y * c.y;
    T d = 2 * cross(b, c);
    return Point<ld>(p1.x + ld(dist12 * c.y - dist23 * b.y) / d, p1.y + ld(dist23 * b.x- dist12 * c.x) / d);
}
template <typename T>
pair<Point<ld>, ld> getSmallestEnclosingCircle(vector<Point<T>> points) { // 평균 O(N)
    mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
    shuffle(points.begin(), points.end(), rng);
    Point<ld> res;
    ld r = -1;
    for (int i = 0; i < points.size(); i++) if (distPP(res, points[i]) > r) {
        res = points[i], r = 0;
        for (int j = 0; j < i; j++) if (distPP(res, points[j]) > r) {
            res = Point<ld>(ld(points[i].x + points[j].x) / 2, ld(points[i].y + points[j].y) / 2), r = distPP(res, points[i]);
            for(int k = 0; k < j; k++) if (distPP(res, points[k]) > r) res = circumcircle(points[i], points[j], points[k]), r = distPP(res, points[k]);
        }
    }
    return {res, r};
}
