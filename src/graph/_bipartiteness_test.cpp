auto isBipartite = [&]() {
	vector<int> vis(n + 1);
	for (int i = 1; i <= n; i++) if (!vis[i]) {
		queue<int> q;
		q.push(i);
		vis[i] = 1;
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			for (int nxt : adj[cur]) {
				if (!vis[nxt]) {
					q.push(nxt);
					vis[nxt] = 3 - vis[cur];
				}
				else if (vis[nxt] == vis[cur]) return false;
			}
		}
	}
	return true;
};