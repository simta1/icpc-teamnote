vector<int> sz(n + 1, 1), in(n + 1), out(n + 1), euler(n + 1);
int dfsi = 0;
auto mkt = [&](auto &&mkt, int cur, int par) -> void {
	in[cur] = ++dfsi;
	euler[in[cur]] = cur;
	for (auto nxt : adj[cur]) if (nxt != par) {
		mkt(mkt, nxt, cur);
		sz[cur] += sz[nxt];
	}
	out[cur] = dfsi;
};
mkt(mkt, 1, -1);

vector<ll> ans(n + 1);
Container c;
auto dfs = [&](auto &&dfs, int cur, int par, bool keep) -> void {
	int h = -1;
	for (auto nxt : adj[cur]) if (nxt != par) {
		if (!~h || sz[h] < sz[nxt]) h = nxt;
	}
	for (auto nxt : adj[cur]) if (nxt != par && nxt != h) {
		dfs(dfs, nxt, cur, 0);
	}
	if (~h) dfs(dfs, h, cur, 1);
	for (auto nxt : adj[cur]) if (nxt != par && nxt != h) {
		for (int i = in[nxt]; i <= out[nxt]; i++) c.insert(euler[i])
	}
	c.insert(cur);
	ans[cur] = sum;
	if (!keep) c = Container();
};
dfs(dfs, 1, -1, 1);

