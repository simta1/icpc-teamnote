template <typename T>
bool half(const Point<T> &p) {
	return p.y < 0 || (p.y == 0 && p.x < 0); // PI <= atan2(p) < 2 * PI
};

sort(planes.begin(), planes.end(), [&](const Point &a, const Point &b) {
	bool ah = half(a), bh = half(b);
	if constexpr (isCCW) return ah != bh ? ah < bh : cross(a, b) > 0;
	else return ah != bh ? ah < bh : cross(a, b) < 0;
});