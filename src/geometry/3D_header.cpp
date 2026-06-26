template <typename T>
struct Point3D {
    T x, y, z;

    Point3D() = default;
    Point3D(T x, T y, T z) : x(x), y(y), z(z) {}
    template <typename U> Point3D(const Point3D<U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}

    bool operator<(const Point3D &other) const { return tie(x, y, z) < tie(other.x, other.y, other.z); }
    Point3D operator-(const Point3D &other) const { return {x - other.x, y - other.y, z - other.z}; }
};
template <typename T>
Point3D<T> crossProduct(const Point3D<T> &p1, const Point3D<T> &p2) {
    return {p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x};
}
template <typename T>
inline T dotProduct(const Point3D<T> &p1, const Point3D<T> &p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}
template <typename T>
ld getTriangleArea(const Point3D<T> &p1, const Point3D<T> &p2, const Point3D<T> &p3) {
    auto [nx, ny, nz] = crossProduct(p2 - p1, p3 - p1);
    return hypot<ld>(nx, ny, nz) / 2;
}
template <typename T>
tuple<T, T, T, T> getEquation(const Point3D<T> &p1, const Point3D<T> &p2, const Point3D<T> &p3) { // ax + by + cz + d = 0
    auto [a, b, c] = crossProduct(p2 - p1, p3 - p1);
    assert(a != 0 || b != 0 || c != 0); // a=b=c=0이면 collinear
    auto d = -(a * p1.x + b * p1.y + c * p1.z);
    return {a, b, c, d};
}
template <typename T1, typename T2>
ld distPF(const Point3D<T1> &p1, const Point3D<T2> &f1, const Point3D<T2> &f2, const Point3D<T2> &f3) { // distance from P(point) to F(face)
    auto normal = crossProduct(f2 - f1, f3 - f1);
    return abs<ld>(dotProduct(normal, p1 - f1)) / hypot<ld>(normal.x, normal.y, normal.z);
}