struct PST {
    struct Node {
        Node *l, *r;
        ll val;
        Node() : l(0), r(0), val(0) {}
    };
    Node* newNode() {
        static Node tree[131'072 * 2 + 18 * 100'000]; // sz * 2 + (1 + log_2(sz)) * q
        static int idx = 0;
        return &tree[idx++];
    }
    int n;
    vector<Node *> roots;
    void build(Node *node, int s, int e, const vector<int> &v) {
        if (s == e) {
            node->val = s < v.size() ? v[s] : 0;
            return;
        }
        int m = s + e >> 1;
        node->l = newNode();
        node->r = newNode();
        build(node->l, s, m, v);
        build(node->r, m + 1, e, v);
        node->val = node->l->val + node->r->val;
    }
    PST(const vector<int> &v) {
        n = v.size();
        roots.push_back(newNode());
        build(roots[0], 0, n - 1, v);
    }
    void update(Node *old, Node *node, int s, int e, int idx, int val) {
        if (s == e) {
            node->val = val;
            return;
        }
        int m = s + e >> 1;
        if (idx <= m) {
            node->l = newNode();
            node->r = old->r;
            update(old->l, node->l, s, m, idx, val);
        }
        else {
            node->l = old->l;
            node->r = newNode();
            update(old->r, node->r, m + 1, e, idx, val);
        }
        node->val = node->l->val + node->r->val;
    }
    void update(int idx, int val) { // 1-based
        roots.push_back(newNode());
        update(*++roots.rbegin(), roots.back(), 0, n - 1, idx - 1, val);
    }
    ll query(Node *node, int s, int e, int l, int r) {
        if (l <= s && e <= r) return node->val;
        if (l > e || s > r) return 0;
        int m = s + e >> 1;
        return query(node->l, s, m, l, r) + query(node->r, m + 1, e, l, r);
    }
    ll query(int t, int l, int r) { // 1-based // t=0은 update한번도 안한 초기v
        return query(roots[t], 0, n - 1, l - 1, r - 1);
    }
};