int sz = 1;
while (sz < q) sz <<= 1;
vector<vector<T>> tree(sz << 1);
auto update = [&](int l, int r, const T &e) {
    for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) tree[l++].push_back(e);
        if (~r & 1) tree[r--].push_back(e);
    }
};

map<T, int> mp;
for (int t = 0; t < q; t++) {
    T e;
    cin >> e;
    if (mp.count(e)) {
        update(mp[e], t - 1, e);
        mp.erase(e);
    }
    else mp[e] = t;
}
for (auto [e, t] : mp) update(t, q - 1, e);

DSU dsu(n);
auto dfs = [&](auto &&dfs, int node, int s, int e) -> void {
    if (q - 1 < s) return;
    int hsz = dsu.h.size();
    for (auto e : tree[node]) dsu.update(e);
    if (s != e) {
        int m = s + e >> 1;
        dfs(dfs, node << 1, s, m);
        dfs(dfs, node << 1 | 1, m + 1, e);
    }
    else cout << dsu.cnt << "\n";
    dsu.rollback(hsz);
};
dfs(dfs, 1, 0, sz - 1);


