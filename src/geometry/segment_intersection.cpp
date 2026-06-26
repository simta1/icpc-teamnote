template <typename T>
bool checkIntersect(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4) {
    int a = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int b = ccw(p3, p4, p1) * ccw(p3, p4, p2);

    if (a > 0 || b > 0) return false;
    if (a < 0 || b < 0) return true;
    return min(p1, p2) <= max(p3, p4) && min(p3, p4) <= max(p1, p2);
}