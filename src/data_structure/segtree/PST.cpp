struct Node {
    int l, r;
    ll val;
    Node() { l = r = val = 0; }
};
vector<Node> tree;
auto newNode = [&]() -> int {
    tree.emplace_back();
    return tree.size() - 1;
};
auto upd = [&](auto &&upd, int old, int s, int e, int i, ll add) {
    int node = newNode();
    tree[node] = tree[old];
    if (s == e) {
        tree[node].val += add;
        return node;
    }
    int m = s + e >> 1;
    if (i <= m) tree[node].l = upd(upd, tree[old].l, s, m, i, add);
    else tree[node].r = upd(upd, tree[old].r, m + 1, e, i, add);
    tree[node].val = tree[tree[node].l].val + tree[tree[node].r].val;
    return node;
};
auto qry = [&](auto &qry, int node, int s, int e, int l, int r) {
    if (l <= s && e <= r) return tree[node].val;
    if (l > e || s > r) return 0LL;
    int m = s + e >> 1;
    return qry(qry, tree[node].l, s, m, l, r) + qry(qry, tree[node].r, m + 1, e, l, r);
};
vector<int> roots = {newNode()}; // version 0