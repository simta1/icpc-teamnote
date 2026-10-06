vector<int> dfsn(n + 1);
int dfsi = 0;
auto dfs = [&](auto &&dfs, int cur, int pid) -> int {
    int low = dfsn[cur] = ++dfsi;
    for (auto [nxt, id] : adj[cur]) if (id != pid) {
        if (!dfsn[nxt]) {
            int nlow = dfs(dfs, nxt, id);
            low = min(low, nlow);
            if (nlow > dfsn[cur]) // id: bridge
        }
        else low = min(low, dfsn[nxt]);
    }
    return low;
};
for (int i = 1; i <= n; i++) if(!dfsn[i]) dfs(dfs, i, -1);
