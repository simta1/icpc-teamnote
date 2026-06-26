// 헤더: Point
template <typename T>
struct SlopeWithIdx {
    int i, j; // idx
    T dx, dy; // 무조건 dx >= 0 되게 저장
    SlopeWithIdx(int i, int j, Point<T> dir) : i(i), j(j), dx(dir.x), dy(dir.y) {}
    bool operator<(const SlopeWithIdx &other) const { return tuple<T, int, int>{dy * other.dx, i, j} < tuple<T, int, int>{other.dy * dx, other.i, other.j}; }
    bool operator==(const SlopeWithIdx &other) const { return dy * other.dx == other.dy * dx; }
};
template <typename T>
void bulldozer(vector<Point<T> > &points) { // O(N^2 logN)
    int n = points.size();
    vector<int> pos(n);
    iota(pos.begin(), pos.end(), 0);
    sort(points.begin(), points.end());
    vector<SlopeWithIdx<T> > slopes;
    slopes.reserve(n * (n - 1) / 2);
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) slopes.emplace_back(i, j, points[j] - points[i]);
    sort(slopes.begin(), slopes.end());
    for (int i = 0, j; i < slopes.size(); i = j) {
        for (j = i; j < slopes.size() && slopes[i] == slopes[j]; j++) {
            int &idx1 = pos[slopes[j].i], &idx2 = pos[slopes[j].j];
            // 인접한 원소끼리 순서를 바뀌며 모든 정렬을 순회하게 됨, 즉 abs(idx1-idx2)==1임
            swap(idx1, idx2);
            swap(points[idx1], points[idx2]);
            
            // idx1이랑 idx2는 pos[]의 alias이므로 함부로 값을 수정하면 안됨
            // 예를 들어 if (idx1 > idx2) swap(idx1, idx2) 같은 거 하면 안됨
            // 그냥 안전하게 i1, i2 선언해서 사용하는 거 추천
            int i1 = min(idx1, idx2);
            int i2 = max(idx1, idx2);
        }
        // slopes[i]의 기울기를 기준으로 정렬되어있음
        // 코드
    }

    // // 점들 뒤집는 nC2개의 모든 과정을 확인
    // for (int i = 0; i < slopes.size(); i++) { // 이 경우 for (auto &slope : slopes)로 해도 무방
    //     int &idx1 = pos[slopes[i].i], &idx2 = pos[slopes[i].j];
    //     swap(idx1, idx2);
    //     swap(points[idx1], points[idx2]);
    //     // 코드
    // }
}
