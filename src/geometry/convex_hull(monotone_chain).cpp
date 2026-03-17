template <typename T>
vector<Point<T> > getConvexHull(vector<Point<T> > points) { // points 원본 배열 바껴도 괜찮으면 &points로 받기 // O(N logN)
    assert (points.size() >= 3);
    sort(points.begin(), points.end());
    vector<Point<T> > upp;
    for (auto &point : points) {
        while (upp.size() >= 2 && ccw(upp[upp.size() - 2], upp[upp.size() - 1], point) >= 0) upp.pop_back();
        upp.push_back(point);
    }
    vector<Point<T> > low;
    for (auto &point : points) {
        while (low.size() >= 2 && ccw(low[low.size() - 2], low[low.size() - 1], point) <= 0) low.pop_back();
        low.push_back(point);
    }
    for (int i = upp.size() - 2; i > 0; i--) low.push_back(upp[i]); // upp과 low의 시작점, 끝점은 중복되는 동일한 점임
    return low; // 반시계 방향 정렬된 상태
}