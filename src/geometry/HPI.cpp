// 헤더: Point, crossProduct, ccw
const ld eps = 1e-9; // epsilon

template <bool isCCW>
struct HalfPlane {
    Point<ld> start, dir; // isCCW=tue일 때 반평면은 dir을 반시계 90도 회전한 방향(dir 왼쪽)에 위치
    template <typename T>
    HalfPlane(const Point<T> &s, const Point<T> &e) : start(s), dir(e - s) {
        ld len = hypot(dir.x, dir.y);
        dir.x /= len;
        dir.y /= len;
    }
    template <typename T>
    HalfPlane(T a, T b, T c) { // ax + by + c >= 0
        assert(a != 0 || b != 0);
        start = (a != 0 ? Point<ld>(-ld(c) / a, 0) : Point<ld>(0, -ld(c) / b));
        // ax + by + c = 0이면 a(x+a) + b(y+b) + c = ax+by+c+a^2+b^2>=0 이므로 (a, b)쪽이 반평면 방향이 되어야 함
        if constexpr (isCCW) dir = {b, -a};
        else dir = {-b, a};
        ld len = hypot(dir.x, dir.y);
        dir.x /= len;
        dir.y /= len;
    }
    template <typename T>
    static HalfPlane<isCCW> getBisector(const Point<T> &a, const Point<T> &b) { // 선분 ab의 수직이등분선이면서 dir이 a를 가리키는 반평면 생성자
        ld sx = ld(a.x + b.x) / 2;
        ld sy = ld(a.y + b.y) / 2;
        if constexpr (isCCW) return HalfPlane<isCCW>(Point<ld>(sx, sy), Point<ld>(sx + (a.y - b.y), sy + (b.x - a.x)));
        else return HalfPlane<isCCW>(Point<ld>(sx, sy), Point<ld>(sx - (a.y - b.y), sy - (b.x - a.x)));
    }
    void move(ld d) {
        if constexpr (isCCW) { // dir 반시계 90도 법선 벡터 : (-dir.y, dir.x)
            start.x -= d * dir.y;
            start.y += d * dir.x;
        }
        else { // dir 시계 90도 법선 벡터 : (dir.y, -dir.x)
            start.x += d * dir.y;
            start.y -= d * dir.x;
        }
    }
    friend bool isParallel(const HalfPlane &a, const HalfPlane &b) { return abs(crossProduct(a.dir, b.dir)) < eps; }
    friend bool isOpposite(const HalfPlane &a, const HalfPlane &b) { return (a.dir.x * b.dir.x + a.dir.y * b.dir.y) < -eps; }
    Point<ld> getPoint(ld k) const {
        return {start.x + k * dir.x, start.y + k * dir.y};
    }
    friend Point<ld> intersectionHH(const HalfPlane &a, const HalfPlane &b) { // assert (!isParallel(a, b))일 때만 호출 됨
        ld k = crossProduct(b.start - a.start, a.dir) / crossProduct(a.dir, b.dir);
        return b.getPoint(k);
    }
    bool include(const Point<ld> &point) { // point가 반평면에 포함되는지
        if constexpr (isCCW) return crossProduct(dir, point - start) > eps;
        else return crossProduct(dir, point - start) < -eps;
    }
    bool include(const HalfPlane &a, const HalfPlane &b) { // a, b의 교점이 반평면에 포함되는지
        return include(intersectionHH(a, b));
    }
};
template <bool isCCW>
vector<Point<ld> > HPI(vector<HalfPlane<isCCW> > planes, ld d=0, bool sortedByAngle=false) { // 반평면들을 각각 거리 d만큼 움직였을 때 교집합 // O(N logN)
    if (!sortedByAngle) { // 이미 선분들이 정렬되어있다면(ex) 볼록다각형의 변들을 순서대로 넣은 경우) sortedByAngle=true 사용
        auto checkQuadrant = [](const HalfPlane<isCCW> &hp) -> bool {
            return hp.dir.y < 0 || (hp.dir.y == 0 && hp.dir.x < 0); // PI <= atan2(dir) < 2 * PI
        };
        sort(planes.begin(), planes.end(), [&](const HalfPlane<isCCW> &a, const HalfPlane<isCCW> &b) {
            bool aq = checkQuadrant(a), bq = checkQuadrant(b);
            if constexpr (isCCW) return aq != bq ? aq < bq : crossProduct(a.dir, b.dir) > 0;
            else return aq != bq ? aq < bq : crossProduct(a.dir, b.dir) < 0;
        });
    }
    vector<int> idxes; idxes.reserve(planes.size());
    for (int i = 0, j; i < planes.size(); i = j) {
        int cur = i;
        j = i + 1;
        while (j < planes.size() && isParallel(planes[i], planes[j])) {
            assert(!isOpposite(planes[i], planes[j]) && "교집합이 다각형으로 제한되지 않고 무한히 넓음");
            if (planes[cur].include(planes[j].start)) cur = j;
            ++j;
        }
        idxes.push_back(cur);
    }
    assert(idxes.size() >= 3 && "교집합이 다각형으로 제한되지 않고 무한히 넓음");
    // assert(!isParallel(planes[0], planes.back()) && "교집합이 다각형으로 제한되지 않고 무한히 넓음");
    assert(!isParallel(planes[idxes[0]], planes[idxes.back()]) && "교집합이 다각형으로 제한되지 않고 무한히 넓음");
    if (d) for (auto &plane : planes) plane.move(d);
    deque<HalfPlane<isCCW> > dq;
    for (auto idx : idxes) {
        auto &plane = planes[idx];
        while (dq.size() >= 2 && !plane.include(dq[dq.size() - 2], dq[dq.size() - 1])) dq.pop_back();
        while (dq.size() >= 2 && !plane.include(dq[0], dq[1])) dq.pop_front();
        if (dq.size() < 2 || dq[0].include(dq.back(), plane)) dq.push_back(plane);
    }
    vector<Point<ld> > res;
    if (dq.size() < 3) return res; // 교집합의 크기가 점 하나에 해당하는 경우 실수오차로 인해 교집합이 없는 것으로 계산되는 경우 생김. 이 경우 distance-=1e-6로 살짝 옮겨주면 잘 계산됨
    for (int i = 0, j = dq.size() - 1; i < dq.size(); j = i++) {
        assert(abs(crossProduct(dq[i].dir, dq[j].dir)) > eps); // TODO 이 줄 그냥 지울까?
        res.push_back(intersectionHH(dq[i], dq[j]));
    }
    assert(dq[1].include(res[0]) && "교집합이 다각형으로 제한되지 않고 무한히 넓음");
    return res; // 리턴값은 볼록 껍질 형태임, isCCW에 따라 볼록껍질 정렬방향 다름(isCCW=true면 반시계방향정렬, isCCW=false면 시계방향정렬)
}

template <typename point_t, typename border_t>
vector<vector<Point<ld> > > getVoronoiDiagram(const vector<Point<point_t> > &points, const vector<Point<border_t> > &border, int dir=0) { // border은 시계/반시계 중 한 방향으로 정렬되있어야 함 // O(N^2 logN) // 중복점있으면안됨
    int n = border.size();
    if (!dir) { // dir은 border에서 점들이 주어진 방향(반시계 : 1, 시계 : -1, 모르는 경우(default) : 0)   
        int i = 2;
        while (!dir && i < n) dir = ccw(border[0], border[1], border[i++]);
    }
    assert(dir != 0); // dir = 0이면 모든 점이 일직선 위에 존재
    n = points.size();
    vector<vector<Point<ld> > > res(n);
    for (int i = 0; i < n; i++) {
        auto [x1, y1] = points[i];
        vector<HalfPlane<true> > planes;
        if (dir == 1) for (int i = 0, j = border.size() - 1; i < border.size(); j = i++) planes.emplace_back(border[j], border[i]);
        else for (int i = 0, j = border.size() - 1; i < border.size(); j = i++) planes.emplace_back(border[i], border[j]);
        for (int j = 0; j < n; j++) if (i != j) planes.emplace_back(HalfPlane<true>::getBisector(points[i], points[j]));
        res[i] = HPI(planes);
    }
    return res;
}

/*
hpi()는 반평면 교집합에 해당하는 다각형의 각 꼭짓점들의 좌표를 한 방향으로 정렬해서 리턴
hpi()에서 반평면 교집합의 크기가 점 하나인 경우 교집합이 없다고 판정될 수 있음.
hpi(planes, 1e-6)처럼 각 변들을 미세하게 음수방향으로 이동시킨 뒤 계산하면 됨
HalfPlane(T a, T b, T c) 생성자 사용시 isCCW는 딱히 신경 쓸 필요없음
HalfPlane(Point<T> &s, Point<T> &e) 생성자 사용할 때는 isCCW 방향 정확히 명시해줘야 함
*/

vector<Point<T> > points(n);
for (auto &[x, y] : points) cin >> x >> y;
// 볼록다각형의 꼭짓점들이 반시계방향 정렬된 경우
vector<HalfPlane<true> > planes;
for (int i = 0, j = n - 1; i < n; j = i++) planes.emplace_back(points[j], points[i]); 
// 볼록다각형의 꼭짓점들이 시계방향 정렬된 경우
vector<HalfPlane<false> > planes;
for (int i = 0, j = n - 1; i < n; j = i++) planes.emplace_back(points[j], points[i]); 