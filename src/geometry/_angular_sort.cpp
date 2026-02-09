auto checkQuadrant = [](const Point &p) -> bool {
	return p.y < 0 || (p.y == 0 && p.x < 0); // PI <= atan2(p) < 2 * PI
};

sort(planes.begin(), planes.end(), [&](const Point &a, const Point &b) {
	bool aq = checkQuadrant(a), bq = checkQuadrant(b);
	if constexpr (isCCW) return aq != bq ? aq < bq : crossProduct(a, b) > 0;
	else return aq != bq ? aq < bq : crossProduct(a, b) < 0;
});