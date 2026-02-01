struct DSU {
	vector<int> parent;
	DSU(int n) : parent(n + 1) {
		iota(parent.begin(), parent.end(), 0);
	}
	int find(int a) {
		return parent[a] == a ? a : parent[a] = find(parent[a]);
	}
	void merge(int a, int b) {
		parent[find(a)] = find(b);
	}
	bool isConnected(int a, int b) {
		return find(a) == find(b);
	}
};