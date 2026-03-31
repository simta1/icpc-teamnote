struct Seg {
	int sz;
	vector<int> tree;
	Seg(int n) {
		sz = 1;
		while (sz < n) sz <<= 1;
		tree.resize(sz << 1);
	}
	void update(int i, int add) { // 0-based
		tree[i |= sz] += add;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	int query(int l, int r) { // 0-based
		int res = 0;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res += tree[l++];
			if (~r & 1) res += tree[r--];
		}
		return res;
	}
	int findKth(int node, int s, int e, int k) { // k만 1-based
		if (s == e) return s; // 0-based
		int m = s + e >> 1;
		if (tree[node << 1] >= k) return findKth(node << 1, s, m, k);
		return findKth(node << 1 | 1, m + 1, e, k - tree[node << 1]);
	}
};