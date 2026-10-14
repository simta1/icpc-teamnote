struct Node {
	int chd[2] = {-1, -1};
};
vector<Node> tree = {Node()};
auto insert = [&](int x) {
	int cur = 0;
	for (int i = 29; i >= 0; i--) {
		int bit = x >> i & 1;
		if (!~tree[cur].chd[bit]) {
			tree[cur].chd[bit] = tree.size();
			tree.emplace_back();
		}
		cur = tree[cur].chd[bit];
	}
};
auto mnqry = [&](int x) {
	int cur = 0;
	for (int i = 29; i >= 0; i--) {
		int bit = x >> i & 1;
		if (!~tree[cur].chd[bit]) bit ^= 1;
		cur = tree[cur].chd[bit];
		x ^= bit << i;
	}
	return x;
};

int f(int x, int k) { // min_{s in {0,1,...,k}} {s ^ x}
	int have = k;
	for(int i = 29; i >= 0; i--) if (x >> i & 1) {
		if (have >= (1 << i)) {
			have -= (1 << i);
			x ^= (1 << i);
		}
	}
	return x;
}