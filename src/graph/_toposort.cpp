auto topoSort = [&](int n, const vector<vector<int>> &adj) { // O(V + E)
    vector<int> indeg(n + 1);
    for (int u = 1; u <= n; u++) for (auto v : adj[u]) ++indeg[v];
    queue<int> q;
    for (int i = 1; i <= n; i++) if (indeg[i] == 0) q.push(i);
    vector<int> res;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        res.push_back(cur);
        for (int nxt : adj[cur]) if (--indeg[nxt] == 0) q.push(nxt);
    }
    bool hasCycle = res.size() != n;
    return {hasCycle, res};
};