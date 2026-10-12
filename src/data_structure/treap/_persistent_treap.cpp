struct Node {
	int l = -1, r = -1;
	int sz = 1, val;
	Node(int val) : val(val) {}
	void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::recalc() { sz = cnt(l) + cnt(r) + 1; }
int clone(int node) {
	tree.push_back(tree[node]);
	return tree.size() - 1;
}
pair<int, int> split(int node, int k) {
	if (!~node) return {-1, -1};
	node = clone(node);
	if (cnt(tree[node].l) >= k) {
		auto [a, b] = split(tree[node].l, k);
		tree[node].l = b;
		tree[node].recalc();
		return {a, node};
	}
	auto [a, b] = split(tree[node].r, k - cnt(tree[node].l) - 1);
	tree[node].r = a;
	tree[node].recalc();
	return {node, b};
}
mt19937 rng;
int merge(int a, int b) {
	if (!~a) return b;
	if (!~b) return a;
	if (rng() % (cnt(a) + cnt(b)) < cnt(a)) {
		a = clone(a);
		tree[a].r = merge(tree[a].r, b);
		tree[a].recalc();
		return a;
	}
	b = clone(b);
	tree[b].l = merge(a, tree[b].l);
	tree[b].recalc();
	return b;
}
int kth(int node, int k) { // k:1-based
	while (1) {
		int lsz = cnt(tree[node].l);
		if (lsz > k - 1) node = tree[node].l;
		else if (lsz == k - 1) return node;
		else {
			k -= lsz + 1;
			node = tree[node].r;
		}
	}
}
void rebuild(int &root) { // 과거 버전 전부 버림
	vector<int> v;
	v.reserve(cnt(root));
	auto dfs = [&](auto &&dfs, int cur) {
		if (!~cur) return;
		dfs(dfs, tree[cur].l);
		v.push_back(tree[cur].val);
		dfs(dfs, tree[cur].r);
	};
	dfs(dfs, root);
	tree.clear();
	auto build = [&](auto &&build, int s, int e) -> int {
		if (s > e) return -1;
		int node = tree.size();
		int m = s + e >> 1;
		tree.emplace_back(v[m]);
		tree[node].l = build(build, s, m - 1);
		tree[node].r = build(build, m + 1, e);
		tree[node].recalc();
		return node;
	};
	root = build(build, 0, v.size() - 1);
}
