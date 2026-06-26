vector<pair<int, int> > getBridges(int n, const vector<vector<int> > &adj) { // O(V + E)
    vector<int> dfsn(n + 1);
    vector<pair<int, int> > res;
    int dfsi = 0;
    function<int(int, int)> dfs = [&](int cur, int parent) -> int {
        int low = dfsn[cur] = ++dfsi;
        for (auto next : adj[cur]) if (next != parent) {
            if (!dfsn[next]) {
                int nextLow = dfs(next, cur);
                low = min(low, nextLow);
                if (nextLow > dfsn[cur]) res.emplace_back(cur, next);
            }
            else low = min(low, dfsn[next]);
        }

        return low;
    };
    for (int i = 1; i <= n; i++) if(!dfsn[i]) dfs(i, -1);
    for (auto &[a, b] : res) if (a > b) swap(a, b);
    return res;
}