struct Node {
    int l, r;
    ll val;
    Node() { l = r = val = 0; }
};
vector<Node> tree;
auto newNode = [&]() {
    tree.emplace_back();
    return tree.size() - 1;
};
auto upd = [&](auto &&upd, int old, int node, int s, int e, int i, int add) {
    if (s == e) {
        tree[node].val = tree[old].val + add;
        return;
    }
    int m = s + e >> 1;
    if (i <= m) {
        tree[node].r = tree[old].r;
        upd(upd, tree[old].l, tree[node].l = newNode(), s, m, i, add);
    }
    else {
        tree[node].l = tree[old].l;
        upd(upd, tree[old].r, tree[node].r = newNode(), m + 1, e, i, add);
    }
    tree[node].val = tree[tree[node].l].val + tree[tree[node].r].val;
};
auto qry = [&](auto &qry, int node, int s, int e, int l, int r) {
    if (l <= s && e <= r) return tree[node].val;
    if (l > e || s > r) return 0LL;
    int m = s + e >> 1;
    return qry(qry, tree[node].l, s, m, l, r) + qry(qry, tree[node].r, m + 1, e, l, r);
};
vector<int> roots;
roots.push_back(newNode()); // version 1