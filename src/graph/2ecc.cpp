vector<int> dfsn(n), eccn(n), s(n);
int dfsi = 0, ecci = 0, top = 0;
auto dfs = [&](auto &&dfs, int cur, int pid) -> int {
    int low = dfsn[cur] = ++dfsi;
    s[top++] = cur;
    for (auto [nxt, id] : adj[cur]) if (id != pid) low = min(low, dfsn[nxt] ?: dfs(dfs, nxt, id));
    if (low == dfsn[cur]) {
        do { eccn[s[--top]] = ecci; } while (s[top] != cur);
        ++ecci;
    }
    return low;
};
for (int i = 0; i < n; i++) if (!dfsn[i]) dfs(dfs, i, -1);
