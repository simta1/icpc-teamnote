// ex) dp[i] : i로부터 가장 먼 정점까지 거리
vector<ll> down(n + 1);
auto dfs = [&](auto &&dfs, int cur, int par) -> void {
	for (auto nxt : adj[cur]) if (nxt != par) {
		dfs(dfs, nxt, cur);
		down[cur] = max(down[cur], down[nxt] + 1);
	}
};
dfs(dfs, 1, -1);

vector<ll> up(n + 1), dp(n + 1);
auto dfs2 = [&](auto &&dfs2, int cur, int par) -> void {
	vector<ll> pref(adj[cur].size());
	for (int i = 0; i < adj[cur].size(); i++) {
		int nxt = adj[cur][i];
		if (nxt == par) pref[i] = up[cur];
		else pref[i] = down[nxt] + 1;
	}
	auto suf = pref;
	for (int i = 1; i < pref.size(); i++) pref[i] = op(pref[i - 1], pref[i]);
	for (int i = int(suf.size()) - 2; i >= 0; i--) suf[i] = op(suf[i], suf[i + 1]);
	dp[cur] = pref.empty() ? 0 : pref.back();
	for (int i = 0; i < adj[cur].size(); i++) {
		int nxt = adj[cur][i];
		if (nxt == par) continue;
		up[nxt] = op(
			i ? pref[i - 1] : 0,
			i + 1 < suf.size() ? suf[i + 1] : 0
		) + 1;
		dfs2(dfs2, nxt, cur);
	}
};
dfs2(dfs2, 1, -1);
