int sz = 1;
while (sz < n) sz <<= 1;
vector<int> tree(sz << 1), cnt(sz << 1);
auto upd = [&](auto &&upd, int node, int s, int e, int l, int r, int add) -> void {
	if (l > e || s > r) return;
	if (l <= s && e <= r) cnt[node] += add;
	else {
		int m = s + e >> 1;
		upd(upd, node << 1, s, m, l, r, add);
		upd(upd, node << 1 | 1, m + 1, e, l, r, add);
	}
	if (cnt[node]) tree[node] = e - s + 1;
	else tree[node] = s != e ? tree[node << 1] + tree[node << 1 | 1] : 0;
};
auto qry = [&]() { return tree[1]; };