// int N = n + 1;
int sz = 1;
while (sz < N) sz <<= 1;
vector<ll> tree(sz << 1), lazy(sz << 1);
auto propagate = [&](int node, int s, int e) {
    if (lazy[node]) {
        tree[node] += (e - s + 1) * lazy[node];
        if (s != e) {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }
        lazy[node] = 0;
    }
};
auto update = [&](auto &&update, int node, int s, int e, int l, int r, ll add) {
    propagate(node, s, e);
    if (l <= s && e <= r) {
        lazy[node] = add;
        propagate(node, s, e);
        return;
    }
    if (l > e || s > r) return;
    int m = s + e >> 1;
    update(update, node << 1, s, m, l, r, add);
    update(update, node << 1 | 1, m + 1, e, l, r, add);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
};
auto query = [&](auto &&query, int node, int s, int e, int l, int r) {
    propagate(node, s, e);
    if (l <= s && e <= r) return tree[node];
    if (l > e || s > r) return 0LL;
    int m = s + e >> 1;
    return query(query, node << 1, s, m, l, r) + query(query, node << 1 | 1, m + 1, e, l, r);
};
