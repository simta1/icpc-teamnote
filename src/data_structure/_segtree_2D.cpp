template <typename T>
T merge(const T &a, const T &b) {
    return a + b;
}

template <typename T>
class SegmentTree1D {
private:
    int n;
    vector<T> tree;

    void init(const vector<T> &v, int node, int s, int e) {
        if (s == e) {
            tree[node] = v[s];
            return;
        }

        int m = s + e >> 1;
        init(v, node * 2, s, m);
        init(v, node * 2 + 1, m + 1, e);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void updateAdd(int node, int s, int e, int i, T val) {
        if (i < s || e < i) return;
        tree[node] = merge(tree[node], val);
        if (s != e) {
            int m = s + e >> 1;
            updateAdd(node * 2, s, m, i, val);
            updateAdd(node * 2 + 1, m + 1, e, i, val);
        }
    }

    T query(int node, int s, int e, int l, int r) {
        if (l <= s && e <= r) return tree[node];
        if (l > e || s > r) return 0;

        int m = s + e >> 1;
        T lq = query(node * 2, s, m, l, r);
        T rq = query(node * 2 + 1, m + 1, e, l, r);
        return merge(lq, rq);
    }

public:
    SegmentTree1D() {} // seg2D에서 vector<seg1D> 초기화할 때 기본 생성자 필요
    SegmentTree1D(int n) : n(n), tree(4 * n) {}
    SegmentTree1D(const vector<T> &v) : n(v.size()), tree(4 * v.size()) {
        init(v, 1, 0, n - 1);
    }

    void updateAdd(int i, T val) {
        updateAdd(1, 0, n - 1, i - 1, val);
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l - 1, r - 1);
    }

    SegmentTree1D operator+(const SegmentTree1D &other) const {
        SegmentTree1D result(n);
        for (int i = 1; i < tree.size(); i++) result.tree[i] = merge(this->tree[i], other.tree[i]);
        return result;
    }
};

template <typename T>
class SegmentTree2D {
private:
    int n;
    vector<vector<T> > v;
    vector<SegmentTree1D<T> > tree;

    void init(int node, int s, int e) {
        if (s == e) {
            tree[node] = SegmentTree1D<T>(v[s]);
            return;
        }

        int m = s + e >> 1;
        init(node * 2, s, m);
        init(node * 2 + 1, m + 1, e);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void updateAdd(int node, int s, int e, int i1, int i2, T val) {
        if (i1 < s || e < i1) return;
        tree[node].updateAdd(i2, val);
        if (s != e) {
            int m = s + e >> 1;
            updateAdd(node * 2, s, m, i1, i2, val);
            updateAdd(node * 2 + 1, m + 1, e, i1, i2, val);
        }
    }

    T query(int node, int s, int e, int l, int r, int l2, int r2) {
        if (l <= s && e <= r) return tree[node].query(l2, r2);
        if (l > e || s > r) return 0;

        int m = s + e >> 1;
        T lq = query(node * 2, s, m, l, r, l2, r2);
        T rq = query(node * 2 + 1, m + 1, e, l, r, l2, r2);
        return merge(lq, rq);
    }

public:
    SegmentTree2D(int n, int m) : n(n), tree(4 * n, SegmentTree1D<T>(m)), v(n, vector<T>(m)) {}
    SegmentTree2D(const vector<vector<T> > &v) : n(v.size()), tree(4 * v.size()), v(v) {
        init(1, 0, n - 1);
    }

    void updateAdd(int x, int y, T val) { // 1-based // O(logN logM)
        updateAdd(1, 0, n - 1, x - 1, y, val);
        v[x - 1][y - 1] += val;
    }
    
    void updateChange(int x, int y, T val) { // 1-based // O(logN logM)
        updateAdd(1, 0, n - 1, x - 1, y, val - v[x - 1][y - 1]);
        v[x - 1][y - 1] = val;
    }

    T query(int x1, int y1, int x2, int y2) { // 1-based // O(logN logM)
        return query(1, 0, n - 1, x1 - 1, x2 - 1, y1, y2);
    }
};