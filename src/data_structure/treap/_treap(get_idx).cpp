struct Node {
	int l = -1, r = -1, p = -1; //
	int pr, sz = 1, val;
	inline static mt19937 rng;
	Node(int val) : pr(rng()), val(val) {}
	void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::recalc() { sz = cnt(l) + cnt(r) + 1; }
pair<int, int> split(int node, int k) {
	if (!~node) return {-1, -1};
	if (cnt(tree[node].l) >= k) {
		auto [a, b] = split(tree[node].l, k);
		tree[node].l = b;
		if (~b) tree[b].p = node; //
		tree[node].p = -1; //
		tree[node].recalc();
		return {a, node};
	}
	auto [a, b] = split(tree[node].r, k - cnt(tree[node].l) - 1);
	tree[node].r = a;
	if (~a) tree[a].p = node; //
	tree[node].p = -1; //
	tree[node].recalc();
	return {node, b};
}
int merge(int a, int b) {
	if (!~a) return b;
	if (!~b) return a;
	if (tree[a].pr > tree[b].pr) {
		tree[a].r = merge(tree[a].r, b);
		tree[tree[a].r].p = a; // 
		tree[a].recalc();
		return a;
	}
	tree[b].l = merge(a, tree[b].l);
	tree[tree[b].l].p = b; // 
	tree[b].recalc();
	return b;
}
int get_idx(int node) { // 0-based
	int res = cnt(tree[node].l);
	while (~tree[node].p) {
		int par = tree[node].p;
		if (tree[par].r == node) res += cnt(tree[par].l) + 1;
		node = par;
	}
	return res;
}
