// 헤더: Point, crossProduct, ccw
// getConvexHull
template <typename T>
T distSquare(const Point<T> &p1, const Point<T> &p2) {
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}
template <typename T>
T getDiameterSquare(const vector<Point<T> > &points, bool isConvex=false) { // O(NlogN)
// isConvex=true할 경우 points가 반시계 정렬되어있어야함. 시계정렬이면 그냥 false로 보내서 사용하기 
    if (points.size() <= 1) return 0;
    if (points.size() == 2) return distSquare(points[0], points[1]);
    const vector<Point<T> > &v = isConvex ? points : getConvexHull(points);
    T diameter = 0;
    int n = v.size(), a = 0, b = 1;
    while (a < n && b < 2 * n) {
        diameter = max(diameter, distSquare(v[a % n], v[b % n]));
        if (crossProduct(v[(a + 1) % n] - v[a % n], v[(b + 1) % n] - v[b % n]) >= 0) ++b;
        else ++a;
    }
    return diameter;
}
template <typename T>
inline T getTriangleAreaDouble(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    return abs(a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x);
}
template <typename T>
T largestTriangleDouble(const vector<Point<T> > &hull) { // O(N^2) // 볼록껍질에 포함되는 가장 큰 삼각형의 넓이
    assert(hull.size() >= 3);
    T res = 0;
    for (int i = 0; i + 2 < hull.size(); i++) {
        for (int j = i + 1, k = i + 2; j < hull.size(); j++) {
            while (k + 1 < hull.size() && getTriangleAreaDouble(hull[i], hull[j], hull[k]) < getTriangleAreaDouble(hull[i], hull[j], hull[k + 1])) ++k;
            res = max(res, getTriangleAreaDouble(hull[i], hull[j], hull[k]));
        }
    }
    return res;
}
