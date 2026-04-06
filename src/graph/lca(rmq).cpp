vector<int> dep(n + 1);
vector<int> euler(2 * n - 1);
vector<int> pos(n + 1);
int sz = 0;
auto mkt = [&](auto &&mkt, int cur, int par) -> void {
    euler[pos[cur] = sz++] = cur;
    for (auto next : adj[cur]) if (next != par) {
        dep[next] = dep[cur] + 1;
        mkt(mkt, next, cur);
        euler[sz++] = cur;
    }
};
mkt(mkt, 1, -1);
vector<vector<int> > ac(__lg(sz) + 1, euler);
for (int i = 1; i <= __lg(sz); i++) {
    for (int j = 0; j + (1 << i) - 1 < sz; j++) {
        int u = ac[i - 1][j];
        int v = ac[i - 1][j + (1 << (i - 1))];
        ac[i][j] = dep[u] < dep[v] ? u : v;
    }
}
auto getLCA = [&](int a, int b) {
    auto [l, r] = minmax(pos[a], pos[b]);
    int i = __lg(r - l + 1);
    int u = ac[i][l];
    int v = ac[i][r - (1 << i) + 1];
    return dep[u] < dep[v] ? u : v;
};
