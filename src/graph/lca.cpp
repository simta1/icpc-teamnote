int mx = __lg(n);
vector<int> dep(n);
vector ac(n, vector<int>(mx + 1));
auto dfs = [&](auto &&dfs, int cur, int par) -> void {
	for (int i = 1; i <= mx; i++) ac[cur][i] = ac[ac[cur][i - 1]][i - 1];
	for (auto nxt : adj[cur]) if (nxt != par) {
		dep[nxt] = dep[cur] + 1;
		ac[nxt][0] = cur;
		dfs(dfs, nxt, cur);
	}
};
ac[0][0] = 0;
dfs(dfs, 0, -1);
auto getLCA = [&](int a, int b) {
	if (dep[a] > dep[b]) swap(a, b);
	for (int diff = dep[b] - dep[a]; diff; diff &= diff - 1) b = ac[b][__builtin_ctz(diff)];
	if (a == b) return a;
	for (int i = mx; i >= 0; i--) if (ac[a][i] != ac[b][i]) a = ac[a][i], b = ac[b][i];
	return ac[a][0];
};
auto getLCA2 = [&](int a, int b, int root) {
	int x = getLCA(root, a);
	int y = getLCA(root, b);
	int res = getLCA(a, b);
	if (dep[res] < dep[x]) res = x;
	if (dep[res] < dep[y]) res = y;
	return res;
};