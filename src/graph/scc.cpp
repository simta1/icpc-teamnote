pair<int, vector<int> > getSCC(int n, const vector<vector<int> > &adj) { // adj는 1-based // O(V+E)
    vector<int> dfsn(n + 1), sccn(n + 1, -1);
    vector<int> s(n);
    int top = 0, dfsi = 0, scci = 0;
    function<int(int)> dfs = [&](int cur) {
        int low = dfsn[cur] = ++dfsi;
        s[top++] = cur;
        for (auto next : adj[cur]) if (!~sccn[next]) low = min(low, dfsn[next] ? dfsn[next] : dfs(next));
        if (low == dfsn[cur]) {
            do { sccn[s[--top]] = scci; } while (s[top] != cur);
            ++scci;
        }
        return low;
    };
    for (int i = 1; i <= n; i++) if (!dfsn[i]) dfs(i);
    for (int i = 1; i <= n; i++) sccn[i] = scci - 1 - sccn[i];
    return {scci, sccn}; // 0-based // scci = scc 개수
}
// graphToDAG(n, adj, sccn)
//     vector<vector<int> > sccs(scci);
//     for (int i = 1; i <= n; i++) sccs[sccn[i]].push_back(i);
//     vector<int> visited(sccs.size(), -1);
//     vector<vector<int> > dag(sccs.size());
//     for (auto &scc : sccs) for (auto u : scc) {
//         for (auto v : adj[u]) if (sccn[v] != sccn[u] && visited[sccn[v]] != sccn[u]) {
//             visited[sccn[v]] = sccn[u];
//             dag[sccn[u]].push_back(sccn[v]);
//         }
//     }