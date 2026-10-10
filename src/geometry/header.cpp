template <typename T>
struct Point {
    T x, y;
    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
    template <typename U> Point(const Point<U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    bool operator<(const Point &other) const { return tie(x, y) < tie(other.x, other.y); }
    bool operator<=(const Point &other) const { return tie(x, y) <= tie(other.x, other.y); }
    bool operator==(const Point &other) const { return tie(x, y) == tie(other.x, other.y); }
    Point operator-(const Point &other) const { return {x-other.x, y-other.y}; }
    Point operator+(const Point &p) const { return {x+p.x, y+p.y}; }
    Point operator*(T k) const { return {x*k, y*k}; }
    Point operator/(T k) const { return {x/k, y/k}; }
    friend T dot(Point a, Point b) { return a.x*b.x+a.y*b.y; }
    friend T cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }
    friend int ccw(Point a, Point b, Point c) {
        T v = cross(b-a,c-a);
        return (v>0)-(v<0);
    }
};
// P: Point, L: Line, S: Segment, H: convexHull, G: polyGon
Point<ld> footPL(const Point<ld> &p, const Point<ld> &a, const Point<ld> &b) {
    auto d = b - a;
    return a + d * (dot(p - a, d) / dot(d, d));
}
Point<ld> reflectPL(const Point<ld> &p, const Point<ld> &a, const Point<ld> &b) {
    return footPL(p, a, b) * 2 - p;
}
template <typename T>
bool onPS(Point<T> p, Point<T> a, Point<T> b) { // p가 l1 l2위에 있는지
    return ccw(a, b, p) == 0 && dot(p - a, p - b) <= 0;
}