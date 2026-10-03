template <typename T>
vector<Point<T>> getConvexHull(vector<Point<T>> ps) { // O(NlogN)
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    if (ps.empty()) return {};
    sort(ps.begin() + 1, ps.end(), [&](const Point<T> &a, const Point<T> &b) {
        int dir = ccw(ps[0], a, b);
        return dir ? dir > 0 : a < b;
    });
    vector<Point<T>> h;
    for (auto &p : ps) {
        while (h.size() >= 2 && ccw(h[h.size() - 2], h[h.size() - 1], p) <= 0) h.pop_back();
        h.push_back(p);
    }
    return h; // 반시계 방향 정렬된 상태
}