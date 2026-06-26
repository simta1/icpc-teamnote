template <typename T>
vector<Point<T> > getConvexHull(vector<Point<T> > points) { // points 원본 배열 바껴도 괜찮으면 &points로 받기 // O(N logN)
    assert (points.size() >= 3);
    swap(points[0], *min_element(points.begin(), points.end()));
    sort(points.begin() + 1, points.end(), [&](const Point<T> &a, const Point<T> &b) {
        int dir = ccw(points[0], a, b);
        return dir ? dir > 0 : a < b;
    });
    vector<Point<T> > v;
    for (auto &point : points) {
        while (v.size() >= 2 && ccw(v[v.size() - 2], v[v.size() - 1], point) <= 0) v.pop_back();
        v.push_back(point);
    }
    return v; // 반시계 방향 정렬된 상태
}