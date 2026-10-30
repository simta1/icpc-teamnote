// addEdge(l, r) : adj[l].push_back(r); // 0<=l<n1, 0<=r<n2
auto bimatch(int n1, int n2, const vector<vector<int>> &adj) { // O(VE) // 0-based
	vector<int> ml(n1, -1), mr(n2, -1), vr(n2);
	int t = 1;
	auto dfs = [&](auto &&dfs, int l) -> bool {
		for (auto r : adj[l]) if (vr[r] != t) {
			vr[r] = t;
			if (!~mr[r] || dfs(dfs, mr[r])) {
				ml[l] = r;
				mr[r] = l;
				return true;
			}
		}
		return false;
	};
	int res = 0;
	for (int l = 0; l < n1; ++l, ++t) res += dfs(dfs, l);
	return tuple{res, ml, mr};
}
auto get_mvc(int n1, int n2, const vector<vector<int>> &adj, const vector<int> &ml, const vector<int> &mr) { // O(V+E) // 0-based
	vector<bool> vl(n1), vr(n2);
	auto dfs = [&](auto &&dfs, int l) -> void {
		vl[l] = true;
		for (auto r : adj[l]) if (~mr[r] && !vr[r] && !vl[mr[r]]) {
			vr[r] = true;
			dfs(dfs, mr[r]);
		}
	};
	for (int l = 0; l < n1; l++) if (!~ml[l]) dfs(dfs, l);
	vector<int> mvcL, mvcR;
	for (int l = 0; l < n1; l++) if (!vl[l]) mvcL.push_back(l);
	for (int r = 0; r < n2; r++) if (vr[r]) mvcR.push_back(r);
	return pair{mvcL, mvcR};
}