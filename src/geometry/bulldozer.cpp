sort(ps.begin(), ps.end());
ps.erase(unique(ps.begin(), ps.end()), ps.end());
int n = ps.size();
vector<pair<int, int>> lines;
for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) lines.emplace_back(i, j);
auto orig = ps;
auto dir = [&](pii p) { return orig[p.second] - orig[p.first]; };
sort(lines.begin(), lines.end(), [&](auto a, auto b) {
	auto c = cross(dir(a), dir(b));
	return c ? c > 0 : a < b;
});
vector<int> pos(n);
iota(pos.begin(), pos.end(), 0);
for (int i = 0, j = 0; i < lines.size(); i = j) {
	while (j < lines.size() && cross(dir(lines[i]), dir(lines[j])) == 0) {
		auto [a, b] = lines[j++];
		// abs(pos[a] - pos[b]) = 1
		swap(ps[pos[a]], ps[pos[b]]);
		swap(pos[a], pos[b]);
	}
	// dir(lines[i]) 오른쪽->왼쪽으로 정렬되어있음
}
