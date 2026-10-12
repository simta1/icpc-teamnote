struct DSU {
	vector<int> p, r;
	vector<array<int, 3>> h;
	int cnt;
	DSU(int n) : p(n), r(n), cnt(n) {
		iota(p.begin(), p.end(), 0);
	}
	int find(int a) {
		while (a != p[a]) a = p[a];
		return a;
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return;
		if (r[a] > r[b]) swap(a, b);
		h.push_back({a, b, r[b]});
		p[a] = b;
		r[b] += r[a] == r[b];
		--cnt;
	}
	void rollback(int sz) {
		while (h.size() > sz) {
			auto [a, b, rb] = h.back();
			h.pop_back();
			p[a] = a;
			r[b] = rb;
			++cnt;
		}
	}
};
