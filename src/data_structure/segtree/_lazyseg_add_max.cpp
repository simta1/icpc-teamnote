struct Seg {
	int sz;
	vector<ll> tree, lazy;
	Seg(int n) {
	// Seg(const vector<ll> &v) {
	//	   int n = v.size();
		sz = 1;
		while (sz < n) sz <<= 1;
		tree.resize(sz << 1);
		lazy.resize(sz << 1);
		// for (int i = 0; i < n; i++) tree[i | sz] = v[i];
		// for (int i = sz - 1; i > 0; i--) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}
	void apply(int node, int s, int e, ll add) {
		tree[node] += add;
		lazy[node] += add;
	}
	void push(int node, int s, int e) {
		if (lazy[node]) {
			int m = s + e >> 1;
			apply(node << 1, s, m, lazy[node]);
			apply(node << 1 | 1, m + 1 , e, lazy[node]);
			lazy[node] = 0;
		}
	}
	void upd(int node, int s, int e, int l, int r, ll add) {
		if (l <= s && e <= r) {
			apply(node, s, e, add);
			return;
		}
		if (l > e || s > r) return;
		push(node, s, e);
		int m = s + e >> 1;
		upd(node << 1, s, m, l, r, add);
		upd(node << 1 | 1, m + 1, e, l, r, add);
		tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
	}
	void upd(int l, int r, ll add) { upd(1, 0, sz - 1, l, r, add); }
	static constexpr ll NEG = numeric_limits<ll>::min();
	ll qry(int node, int s, int e, int l, int r) {
		if (l <= s && e <= r) return tree[node];
		if (l > e || s > r) return NEG;
		push(node, s, e);
		int m = s + e >> 1;
		return max(qry(node << 1, s, m, l, r), qry(node << 1 | 1, m + 1, e, l, r));
	}
	ll qry(int l, int r) { return qry(1, 0, sz - 1, l, r); }
};
