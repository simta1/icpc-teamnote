struct Node {
	ll val, lazy = 0;
	int l = -1, r = -1;
	int pr, sz = 1;
	inline static mt19937 rng;
	Node(ll val) : val(val), pr(rng()) {}
	void apply(ll add);
	void push();
	void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::apply(ll add) {
	val += add;
	lazy += add;
}
void Node::push() {
	if (!lazy) return;
	if (~l) tree[l].apply(lazy);
	if (~r) tree[r].apply(lazy);
	lazy = 0;
}
void Node::recalc() {
	sz = 1;
	if (~l) sz += tree[l].sz;
	if (~r) sz += tree[r].sz;
}
pair<int, int> split(int node, int k) {
	if (!~node) return {-1, -1};
	tree[node].push();
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
	tree[a].push();
	tree[b].push();
	if (tree[a].pr > tree[b].pr) {
		tree[a].r = merge(tree[a].r, b);
		tree[a].recalc();
		return a;
	}
	tree[b].l = merge(a, tree[b].l);
	tree[b].recalc();
	return b;
}

pair<int, int> splitByValue(int node, ll x) { // {x이하, x초과}
	if (!~node) return {-1, -1};
	tree[node].push();
	if (tree[node].val > x) {
		auto [a, b] = splitByValue(tree[node].l, x);
		tree[node].l = b;
		tree[node].recalc();
		return {a, node};
	}
	auto [a, b] = splitByValue(tree[node].r, x);
	tree[node].r = a;
	tree[node].recalc();
	return {node, b};
}
void insert(int &root, ll val) {
    int node = tree.size();
    tree.emplace_back(val);
    auto [a, b] = splitByValue(root, val);
    root = merge(merge(a, node), b);
}

ll mnqry(int node) {
	while (~tree[node].l) {
		tree[node].push();
		node = tree[node].l;
	}
	return tree[node].val;
}
void descLargest(int &root, int k) {
    auto [a, b] = split(root, cnt(root) - k);
    tree[b].apply(-1);
    ll x = mnqry(b);
    auto [a0, a1] = splitByValue(a, x - 1);
    auto [b0, b1] = splitByValue(b, x);
    if (x == 0) b0 = -1;
    root = merge(merge(merge(a0, b0), a1), b1);
}
