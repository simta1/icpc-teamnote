auto isBipartite = [&]() {
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        queue<int> q;
        q.push(i);
        vis[i] = 1;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int next : adj[cur]) {
                if (!vis[next]) {
                    q.push(next);
                    vis[next] = 3 - vis[cur];
                }
                else if (vis[next] == vis[cur]) return false;
            }
        }
    }
    return true;
};