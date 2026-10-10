vector<Point<ld>> clipHL(const vector<Point<ld>> &poly, Point<ld> a, Point<ld> b) { // a->b의 왼쪽만 남김
    vector<Point<ld>> res;
    for (int i = 0, j = int(poly.size()) - 1; i < poly.size(); j = i++) {
        auto p = poly[j], q = poly[i];
        ld s = cross(b - a, p - a), t = cross(b - a, q - a);
        if (s >= 0) res.push_back(p);
        if ((s < 0 && t > 0) || (s > 0 && t < 0)) res.push_back(p + (q - p) * (s / (s - t)));
    }
    return res;
}
vector<Point<ld>> interHH(vector<Point<ld>> a, const vector<Point<ld>> &b) { // O(M(N+M))
    // b는 반시계여야 됨
    if (b.empty()) return {};
    for (int i = 0, j = b.size() - 1; i < b.size(); j = i++) a = clipHL(a, b[j], b[i]);
    return a;
}
