auto bimatch(int n1, int n2, const vector<vector<int>> &adj) { // O(E sqrt(V)) // 0-based
	vector<int> ml(n1, -1), mr(n2, -1), lvl(n1), ptr(n1);
	auto bfs = [&]() -> bool {
		queue<int> q;
		for (int l = 0; l < n1; l++) {
			if (!~ml[l]) {
				lvl[l] = 0;
				q.push(l);
			}
			else lvl[l] = -1;
		}
		bool flag = false;
		while (!q.empty()) {
			int l = q.front();
			q.pop();
			for (auto r : adj[l]) {
				if (!~mr[r]) flag = true;
				else if (!~lvl[mr[r]]) {
					lvl[mr[r]] = lvl[l] + 1;
					q.push(mr[r]);
				}
			}
		}
		return flag;
	};
	auto dfs = [&](auto &&dfs, int l) -> bool {
		for (int &i = ptr[l]; i < adj[l].size(); i++) {
			int r = adj[l][i];
			if (!~mr[r] || lvl[mr[r]] == lvl[l] + 1 && dfs(dfs, mr[r])) {
				ml[l] = r;
				mr[r] = l;
				return true;
			}
		}
		return false;
	};
	int res = 0;
	while (bfs()) {
		fill(ptr.begin(), ptr.end(), 0);
		for (int l = 0; l < n1; l++) res += (!~ml[l] && dfs(dfs, l));
	}
	return tuple{res, ml, mr};
}