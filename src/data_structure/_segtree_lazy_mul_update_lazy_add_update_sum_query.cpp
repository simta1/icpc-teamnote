constexpr ll MOD = 998'244'353;
int sz = 1;
while (sz < n) sz <<= 1;
vector<ll> tree(sz << 1), lm(sz << 1, 1), la(sz << 1);
auto propagate = [&](int node, int s, int e) {
    if (lm[node] != 1 || la[node]) {
        tree[node] = (tree[node] * lm[node] + (e - s + 1) * la[node]) % MOD;
        if (s != e) {
            for (auto next : {node << 1, node << 1 | 1}) {
                lm[next] = lm[next] * lm[node] % MOD;
                la[next] = (la[next] * lm[node] + la[node]) % MOD;
            }
        }
        lm[node] = 1;
        la[node] = 0;
    }
};
auto update = [&](auto &&update, int node, int s, int e, int l, int r, ll mul, ll add) {
    propagate(node, s, e);
    if (l <= s && e <= r) {
        lm[node] = mul;
        la[node] = add;
        propagate(node, s, e);
        return;
    }
    if (l > e || s > r) return;
    int m = s + e >> 1;
    update(update, node << 1, s, m, l, r, mul, add);
    update(update, node << 1 | 1, m + 1, e, l, r, mul, add);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
    if (tree[node] >= MOD) tree[node] -= MOD;
};
auto query = [&](auto &&query, int node, int s, int e, int l, int r) {
    propagate(node, s, e);
    if (l <= s && e <= r) return tree[node];
    if (l > e || s > r) return 0LL;
    int m = s + e >> 1;
    ll res = query(query, node << 1, s, m, l, r) + query(query, node << 1 | 1, m + 1, e, l, r);
    return res >= MOD ? (res - MOD) : res;
};
// update(update, 1, 0, sz - 1, x - 1, y - 1, 1, v); // range add
// update(update, 1, 0, sz - 1, x - 1, y - 1, v, 0); // range mul
// update(update, 1, 0, sz - 1, x - 1, y - 1, 0, v); // range change
