template <typename T>
struct BIT {
    vector<T> tree;
    BIT(int n) : tree(n + 1) {}
    void update(int i, T val) { // 1-based
        for (; i < tree.size(); i += (i & -i)) tree[i] += val;
    }
    T query(int l, int r) { // 1-based
        T res = 0;
        for (int i = r; i > 0; i -= (i & -i)) res += tree[i];
        for (int i = l - 1; i > 0; i -= (i & -i)) res -= tree[i];
        return res;
    }
    int findKth(T k) { // 1-based
        int n = tree.size() - 1;
        assert(n > 0);
        if (k <= 0) return 0;
        int res = 0;
        for (int i = 1 << 31 - __builtin_clz(n); i > 0; i >>= 1) {
            if (res + i <= n && tree[res + i] < k) {
                res += i;
                k -= tree[res];
            }
        }
        return res;
    }
};