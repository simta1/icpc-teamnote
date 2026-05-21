struct DSU {
	vector<int> p;
	DSU(int n) : p(n + 1) {
		iota(p.begin(), p.end(), 0);
	}
	int find(int a) {
		while (p[a] != a) a = p[a] = p[p[a]];
		return a;
	}
	void merge(int a, int b) {
		p[find(a)] = find(b);
	}
};