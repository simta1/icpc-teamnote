// 1-based (ac default값이 0이라서 0-based안됨)
int mx = __lg(n);
vector<int> dep(n + 1);
vector ac(n + 1, vector<int>(mx + 1));
auto dfs = [&](auto &&dfs, int cur, int par) -> void {
    for (auto next : adj[cur]) if (next != par) {
        dep[next] = dep[cur] + 1;
        ac[next][0] = cur;
        for (int i = 1; i <= mx; i++) ac[next][i] = ac[ac[next][i - 1]][i - 1];
        dfs(dfs, next, cur);
    }
};
dfs(dfs, 1, -1); // O(NlogN)
auto getLCA = [&](int a, int b) { // O(logN)
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