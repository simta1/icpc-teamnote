vector<int> dep(n + 1), pos(n + 1), euler(2 * n - 1);
int ei = 0;
auto mkt = [&](auto &&mkt, int cur, int par) -> void {
    euler[pos[cur] = ei++] = cur;
    for (auto nxt : adj[cur]) if (nxt != par) {
        dep[nxt] = dep[cur] + 1;
        mkt(mkt, nxt, cur);
        euler[ei++] = cur;
    }
};
mkt(mkt, 1, -1);
vector<vector<int>> ac(__lg(ei) + 1, euler);
for (int i = 1; i <= __lg(ei); i++) {
    for (int j = 0; j + (1 << i) - 1 < ei; j++) {
        int u = ac[i - 1][j];
        int v = ac[i - 1][j + (1 << i - 1)];
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
