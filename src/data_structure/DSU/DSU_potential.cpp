template <typename T>
struct DSU {
	vector<int> p;
	vector<T> w;
	DSU(int n) : p(n + 1), w(n + 1) {
		iota(p.begin(), p.end(), 0);
	}
	int find(int a) {
		if (p[a] == a) return a;
		int ra = find(p[a]); // w[p[a]] 계산
		w[a] += w[p[a]];
		return p[a] = ra;
	}
	void merge(int a, int b, T val) { // b = a + val
		int ra = find(a);
		int rb = find(b);
		w[rb] = w[a] + val - w[b];
		p[rb] = ra;
	}
	T getDiff(int a, int b) {
		int ra = find(a);
		int rb = find(b);
		assert(ra == rb);
		return w[b] - w[a];
	}
};
