struct Node {
	int l = -1, r = -1;
	ll sum = 0;
	int pr, sz = 1, val;
	bool flip = false;
	inline static mt19937 rng;
	Node(int val) : sum(val), pr(rng()), val(val) {}
	void propagate();
	void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::propagate() {
	if (!flip) return;
	swap(l, r);
	if (~l) tree[l].flip ^= 1;
	if (~r) tree[r].flip ^= 1;
	flip = 0;
}
void Node::recalc() {
	sz = 1;
	sum = val;
	if (~l) {
		tree[l].propagate();
		sz += tree[l].sz;
		sum += tree[l].sum;
	}
	if (~r) {
		tree[r].propagate();
		sz += tree[r].sz;
		sum += tree[r].sum;
	}
}
pair<int, int> split(int node, int k) {
	if (!~node) return {-1, -1};
	tree[node].propagate();
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
int merge(int a, int b) {
	if (!~a) return b;
	if (!~b) return a;
	tree[a].propagate();
	tree[b].propagate();
	if (tree[a].pr > tree[b].pr) {
		tree[a].r = merge(tree[a].r, b);
		tree[a].recalc();
		return a;
	}
	tree[b].l = merge(a, tree[b].l);
	tree[b].recalc();
	return b;
}
void reverse(int &root, int l, int r) {
	auto [a, bc] = split(root, l);
	auto [b, c] = split(bc, r - l + 1);
	tree[b].flip ^= 1;
	root = merge(merge(a, b), c);
}
ll query(int &root, int l, int r) {
	auto [a, bc] = split(root, l);
	auto [b, c] = split(bc, r - l + 1);
	ll res = tree[b].sum;
	root = merge(merge(a, b), c);
	return res;
}
