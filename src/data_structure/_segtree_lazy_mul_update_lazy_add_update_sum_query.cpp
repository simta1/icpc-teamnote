constexpr ll MOD = 1e9 + 7;
inline ll getSum(ll a, ll b) {
    ll res = a + b;
    return res >= MOD ? res - MOD : res;
}

struct Node {
    ll sum = 0, lm = 1, la = 0;
};

vector<Node> tree;

void propagate(int node, int s, int e) {
    if (tree[node].la || tree[node].lm != 1) {
        tree[node].sum = (tree[node].sum * tree[node].lm + (e - s + 1) * tree[node].la) % MOD;
        if (s != e) {
            for (auto next : {node << 1, node << 1 | 1}) {
                tree[next].lm = (tree[next].lm * tree[node].lm) % MOD;
                tree[next].la = (tree[next].la * tree[node].lm + tree[node].la) % MOD;
            }
        }
        tree[node].lm = 1;
        tree[node].la = 0;
    }
}

ll query(int node, int s, int e, int l, int r) {
    propagate(node, s, e);
    if (l <= s && e <= r) return tree[node].sum;
    if (l > e || s > r) return 0;
    int m = s + e >> 1;
    return getSum(query(node << 1, s, m, l, r), query(node << 1 | 1, m + 1, e, l, r));
}

void update(int node, int s, int e, int l, int r, ll mul, ll add) {
    propagate(node, s, e);
    if (l <= s && e <= r) {
        tree[node].lm = mul;
        tree[node].la = add;
        propagate(node, s, e);
        return;
    }
    if (l > e || s > r) return;
    int m = s + e >> 1;
    update(node << 1, s, m, l, r, mul, add);
    update(node << 1 | 1, m + 1, e, l, r, mul, add);
    tree[node].sum = getSum(tree[node << 1].sum, tree[node << 1 | 1].sum);
}

// update(1, 0, sz - 1, x - 1, y - 1, 1, v); // range add
// update(1, 0, sz - 1, x - 1, y - 1, v, 0); // range mul
// update(1, 0, sz - 1, x - 1, y - 1, 0, v); // range change
