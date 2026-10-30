template <typename F>
struct CIR {
	int n;
	Dinic<F> dinic;
	vector<F> demand;
	CIR(int n) : n(n), dinic(n + 2), demand(n) {}
	void addEdge(int a, int b, F l, F r) {
		demand[a] += l;
		demand[b] -= l;
		if (r > l) dinic.addEdge(a, b, r == INF ? r : r - l);
	}
	bool circulation() {
		int s2 = n, t2 = n + 1;
		F need = 0;
		for (int i = 0; i < n; i++) {
			if (demand[i] > 0) {
				need += demand[i];
				dinic.addEdge(i, t2, demand[i]);
			}
			else if (demand[i] < 0) dinic.addEdge(s2, i, -demand[i]);
		}
		return dinic.maxFlow(s2, t2) == need;
	}
	F lrflow(int s, int t) {
		int idx = dinic.adj[t].size();
		dinic.addEdge(t, s, numeric_limits<F>::max());
		if (!circulation()) return -1;
		auto &e = dinic.adj[t][idx];
		F base = e.flow();
		dinic.adj[s][e.rev].c = e.c = 0;
		return base + dinic.maxFlow(s, t);
	}
};
