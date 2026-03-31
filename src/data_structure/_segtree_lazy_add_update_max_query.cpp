auto propagate = [&](int node, int s, int e) {
	if (lazy[node]) {
		tree[node] += lazy[node];
		if (s != e) {
			lazy[node << 1] += lazy[node];
			lazy[node << 1 | 1] += lazy[node];
		}
		lazy[node] = 0;
	}
};
function<void(int, int, int, int, int, ll)> update = [&](int node, int s, int e, int l, int r, ll add) {
	propagate(node, s, e);
	if (l <= s && e <= r) {
		lazy[node] = add;
		propagate(node, s, e);
		return;
	}
	if (l > e || s > r) return;
	int m = s + e >> 1;
	update(node << 1, s, m, l, r, add);
	update(node << 1 | 1, m + 1, e, l, r, add);
	tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
};
constexpr ll INF = 1e18;
function<ll(int, int, int, int, int)> query = [&](int node, int s, int e, int l, int r) {
	propagate(node, s, e);
	if (l <= s && e <= r) return tree[node];
	if (l > e || s > r) return -INF;
	int m = s + e >> 1;
	return max(query(node << 1, s, m, l, r), query(node << 1 | 1, m + 1, e, l, r));
};
