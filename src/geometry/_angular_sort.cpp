auto half = [&](auto &p) {
	return p.y < 0 || (p.y == 0 && p.x < 0); // PI <= atan2(p) < 2 * PI
};

sort(ps.begin(), ps.end(), [&](auto &a, auto &b) {
	bool ah = half(a), bh = half(b);
	if constexpr (isCCW) return ah != bh ? ah < bh : cross(a, b) > 0;
	else return ah != bh ? ah < bh : cross(a, b) < 0;
});