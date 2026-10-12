constexpr ll MOD = 998'244'353;
struct Node {
	int l = -1, r = -1;
	ll sum, lm = 1, la = 0, val;
	int pr, sz = 1;
	bool flip = false;
	inline static mt19937 rng;
	Node(int val) : sum(val), val(val), pr(rng()) {}
	void propagate();
	void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::propagate() {
	if (flip) {
		swap(l, r);
		if (~l) tree[l].flip ^= 1;
		if (~r) tree[r].flip ^= 1;
		flip = 0;
	}
	if (lm != 1 || la) {
		val = (val * lm + la) % MOD;
		sum = (sum * lm + la * sz) % MOD;
		for (auto nxt : {l, r}) if (~nxt) {
			tree[nxt].lm = tree[nxt].lm * lm % MOD;
			tree[nxt].la = (tree[nxt].la * lm + la) % MOD;
		}
		lm = 1;
		la = 0;
	}
}
void Node::recalc() {
	sz = 1;
	sum = val;
	if (~l) {
		tree[l].propagate();
		sz += tree[l].sz;
		sum += tree[l].sum;
		if (sum >= MOD) sum -= MOD;
	}
	if (~r) {
		tree[r].propagate();
		sz += tree[r].sz;
		sum += tree[r].sum;
		if (sum >= MOD) sum -= MOD;
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
void insert(int &root, int idx, int node) {
	auto [a, b] = split(root, idx);
	root = merge(merge(a, node), b);
}
void erase(int &root, int idx) {
	auto [a, bc] = split(root, idx);
	auto [b, c] = split(bc, 1);
	root = merge(a, c);
}

template <typename F>
void f(int &root, int l, int r, F f) {
	auto [a, bc] = split(root, l);
	auto [b, c] = split(bc, r - l + 1);
	assert(~b);
	f(b); // split후라서 b는 propagate된 상태
	root = merge(merge(a, b), c);
}

// reverse(root, l, r)
f(root, l, r, [&](int node) {
	tree[node].flip ^= 1;
});
// update(root, l, r, mul, add)
f(root, l, r, [&](int node) {
	tree[node].lm = mul;
	tree[node].la = add;
});
// query(root, l, r)
f(root, l, r, [&](int node) {
	cout << tree[node].sum << "\n";
});
