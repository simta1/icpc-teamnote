vector<vector<int>> chd(n);
vector<int> sz(n, 1), dep(n), p(n), in(n), top(n);
auto mkt = [&](auto &&mkt, int cur, int par) -> void {
    for (auto nxt : adj[cur]) if (nxt != par) {
        p[nxt] = cur;
        dep[nxt] = dep[cur] + 1;
        mkt(mkt, nxt, cur);
        chd[cur].push_back(nxt);
        sz[cur] += sz[nxt];
        if (sz[chd[cur][0]] < sz[nxt]) swap(chd[cur][0], chd[cur].back());
    }
};
mkt(mkt, root, -1);
int dfsi = 0;
auto ett = [&](auto &&ett, int cur) -> void {
    in[cur] = ++dfsi;
    for (auto nxt : chd[cur]) {
        top[nxt] = (nxt == chd[cur][0] ? top[cur] : nxt);
        ett(ett, nxt);
    }
};
top[root] = root;
ett(ett, root);
segtree seg(n);
auto query = [&](int a, int b) { // O(log^2N)
    int res = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]]) swap(a, b);
        res += seg.query(in[top[b]], in[b]);
        b = p[top[b]];
    }
    if (dep[a] > dep[b]) swap(a, b);
    res += seg.query(in[a], in[b]); // 정점쿼리
    // if (in[a] + 1 <= in[b]) res += seg.query(in[a] + 1, in[b]); // 간선쿼리
    return res;
};
// seg.update(in[a], b);
// ett: [in[cur], in[cur] + sz[cur] - 1]