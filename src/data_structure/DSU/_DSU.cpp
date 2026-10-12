struct DSU {
	vector<int> p;
	DSU(int n) : p(n) {
		iota(p.begin(), p.end(), 0);
	}
	int find(int a) {
		return a == p[a] ? a : p[a] = find(p[a]);
	}
	void merge(int a, int b) {
		p[find(a)] = find(b);
	}
};