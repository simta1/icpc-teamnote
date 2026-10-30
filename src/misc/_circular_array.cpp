// ex) 반평면 순회
// vector<Point> v(n);
T acc = 0;
for (int i = 0, j = 1; i < n; i++) {
	j = max(j, i + 1);
	while (j < i + n && cross(v[i], v[j % n]) >= 0) acc += f(v[j++ % n]);
	// acc := sum(f(v[k % n])), k in [i+1:j)
	if (i + 1 < j) acc -= f(v[(i + 1) % n]);
}
