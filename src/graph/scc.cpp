auto getSCC(int n, const vector<vector<int>> &adj) { // adj: 0-based // O(V+E)
	vector<int> dfsn(n), sccn(n, -1);
	vector<int> s(n);
	int top = 0, dfsi = 0, scci = 0;
	auto dfs = [&](auto &&dfs, int cur) -> int {
		int low = dfsn[cur] = ++dfsi;
		s[top++] = cur;
		for (auto nxt : adj[cur]) if (!~sccn[nxt]) low = min(low, dfsn[nxt] ? dfsn[nxt] : dfs(dfs, nxt));
		if (low == dfsn[cur]) {
			do { sccn[s[--top]] = scci; } while (s[top] != cur);
			++scci;
		}
		return low;
	};
	for (int i = 0; i < n; i++) if (!dfsn[i]) dfs(dfs, i);
	for (int i = 0; i < n; i++) sccn[i] = scci - 1 - sccn[i];
	return pair{scci, sccn}; // 0-based // scci = scc 개수
}
// 1-based인 경우 사용법
// auto [scci, sccn] = getSCC(n + 1, adj);
// --scci; // 정점 0 제외

// graphToDAG(n, adj, sccn) // 0-based
//	   vector<vector<int>> sccs(scci);
//	   for (int i = 0; i < n; i++) sccs[sccn[i]].push_back(i);
//	   vector<int> visited(sccs.size(), -1);
//	   vector<vector<int>> dag(sccs.size());
//	   for (auto &scc : sccs) for (auto u : scc) {
//		   for (auto v : adj[u]) if (sccn[v] != sccn[u] && visited[sccn[v]] != sccn[u]) {
//			   visited[sccn[v]] = sccn[u];
//			   dag[sccn[u]].push_back(sccn[v]);
//		   }
//	   }
