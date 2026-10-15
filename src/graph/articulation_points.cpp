vector<int> dfsn(n + 1);
int dfsi = 0;
auto dfs = [&](auto &&dfs, int cur, int parent) -> int {
	int low = dfsn[cur] = ++dfsi, child = 0;
	bool cutP = 0;
	for (auto nxt : adj[cur]) if (nxt != parent) {
		if (!dfsn[nxt]) {
			++child;
			int nlow = dfs(dfs, nxt, cur);
			low = min(low, nlow);
			cutP |= nlow >= dfsn[cur];
		}
		else low = min(low, dfsn[nxt]);
	}
	if (!~parent ? child > 1 : cutP) ; // cur은 단절점
	return low;
};
for (int i = 1; i <= n; i++) if(!dfsn[i]) dfs(dfs, i, -1);