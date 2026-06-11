template<typename T, T (*op)(T, T), T (*e)()>
struct Seg {
    int sz;
    vector<T> tree;
    Seg(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1, e());
    }
    void update(int i, T val) { // 0-based
        tree[i |= sz] = val;
        while (i >>= 1) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    T query(int l, int r) { // 0-based
        if (l > r) return e();
        T resL = e(), resR = e();
        for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) resL = op(resL, tree[l++]);
            if (~r & 1) resR = op(tree[r--], resR);
        }
        return op(resL, resR);
    }
};
