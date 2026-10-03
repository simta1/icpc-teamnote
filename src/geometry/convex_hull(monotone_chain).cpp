template <typename T>
vector<Point<T>> getConvexHull(vector<Point<T>> ps) { // O(NlogN)
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    if (ps.size() <= 1) return ps;
    vector<Point<T>> h;
    for (auto x : ps) {
        while (h.size() >= 2 && ccw(h[h.size() - 2], h.back(), x) <= 0) h.pop_back();
        h.push_back(x);
    }
    int lower = h.size();
    for (int i = ps.size() - 2; i >= 0; i--) {
        while (h.size() > lower && ccw(h[h.size() - 2], h.back(), ps[i]) <= 0) h.pop_back();
        h.push_back(ps[i]);
    }
    h.pop_back();
    return h;
}