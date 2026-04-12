vector<int> dfn(n + 1), eccn(n + 1), s(n);
int dfsi = 0, ecci = 0, top = 0;
auto dfs = [&](auto &&dfs, int cur, int par) -> int {
    int low = dfn[cur] = ++dfsi;
    s[top++] = cur;
    for (auto next : adj[cur]) if (next != par) low = min(low, dfn[next] ?: dfs(dfs, next, cur));
    if (low == dfn[cur]) {
        ++ecci;
        do { eccn[s[--top]] = ecci; } while (s[top] != cur);
    }
    return low;
};

dfs(dfs, 1, -1);
