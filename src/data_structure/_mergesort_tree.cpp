vector<vector<int> > tree(4 * n);
auto build = [&](auto &&build, int node, int s, int e) -> void {
    if (s == e) {
        tree[node].push_back(v[s]);
        return;
    }
    int m = s + e >> 1;
    build(build, node << 1, s, m);
    build(build, node << 1 | 1, m + 1, e);
    auto &l = tree[node << 1];
    auto &r = tree[node << 1 | 1];
    merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(tree[node]));
};
build(build, 1, 0, n - 1);

auto query = [&](auto &&query, int node, int s, int e, int l, int r, int val) -> int {
    if (l <= s && e <= r) return upper_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
    if (l > e || s > r) return 0;
    int m = s + e >> 1;
    return query(query, node << 1, s, m, l, r, val) + query(query, node << 1 | 1, m + 1, e, l, r, val);
};