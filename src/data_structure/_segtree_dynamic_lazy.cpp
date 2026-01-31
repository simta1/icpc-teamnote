// only updateAdd
template <typename idx_t, typename T>
class DynamicLazySeg {
private:
    struct Node {
        T val;
        T lazy;
        int l, r;

        Node(T val) : val(val), lazy(0), l(0), r(0) {}
        Node() : Node(0) {} // 항등원
    };

    T merge(const T &a, const T &b) { return a + b; }

    vector<Node> tree;
    const int root = 1;
    const idx_t MAX_IDX;

    int newNode() { tree.push_back(Node()); return tree.size() - 1; }

    void propagate(int node, int s, int e) {
        if (!node) return; // tree[0].val은 항상 항등원으로 유지되어야 함

        if (!tree[node].lazy) return;

        tree[node].val += (e - s + 1) * tree[node].lazy;
        if (s != e) {
            if (!tree[node].l) tree[node].l = newNode();
            tree[tree[node].l].lazy += tree[node].lazy;
            if (!tree[node].r) tree[node].r = newNode();
            tree[tree[node].r].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }

    bool haveOverlap(idx_t s, idx_t e, idx_t l, idx_t r) {
        return !(r < s || e < l);
    }

    // 항상 haveOverlap()으로 확인된 구간만 들어옴, 구간이 하나도 겹치지 않는 경우는 애초에 없음
    void update(int node, idx_t s, idx_t e, idx_t l, idx_t r, T val, bool add) {
        if (l <= s && e <= r) {
            tree[node].lazy += val;
        }
        else {
            idx_t m = s + e >> 1;
            if (haveOverlap(s, m, l, r)) {
                if(!tree[node].l) tree[node].l = newNode();
                update(tree[node].l, s, m, l, r, val, add);
            }
            if (haveOverlap(m + 1, e, l, r)) {
                if(!tree[node].r) tree[node].r = newNode();
                update(tree[node].r, m + 1, e, l, r, val, add);
            }
            tree[node].val += val * (min(e, r) - max(s, l) + 1);
        }
    }

    T query(int node, idx_t s, idx_t e, idx_t l, idx_t r) {
        if (!node) return tree[0].val; // dummy
        propagate(node, s, e);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node].val;

        idx_t m = s + e >> 1;
        T lq = haveOverlap(s, m, l, r) ? query(tree[node].l, s, m, l, r) : tree[0].val;
        T rq = haveOverlap(m + 1, e, l, r) ? query(tree[node].r, m + 1, e, l, r) : tree[0].val;
        return merge(lq, rq);
    }

public:
    DynamicLazySeg(idx_t maxIdx) : MAX_IDX(maxIdx), tree(2) {} // tree[0] : dummy, tree[1] : root

    void reserve(int sz) { if (sz > tree.capacity()) tree.reserve(sz); } // array doubling 최소화

    void updateAdd(idx_t l, idx_t r, T val) { // 0 <= i <= MAX_IDX
        assert(haveOverlap(0, MAX_IDX, l, r));
        update(root, 0, MAX_IDX, l, r, val, 1);
    }

    void updateAdd(idx_t idx, T val) { // 0 <= i <= MAX_IDX
        assert(haveOverlap(0, MAX_IDX, idx, idx));
        update(root, 0, MAX_IDX, idx, idx, val, 1);
    }

    T query(idx_t l, idx_t r) { // 0 <= l <= r <= MAX_IDX
        return query(root, 0, MAX_IDX, l, r);
    }
};

// updateAdd + updateChange
template <typename idx_t, typename T>
class DynamicLazySeg {
private:
    struct __attribute__((__packed__)) Node {
        T val, lazy;
        int l, r;
        bool lazyKind; // 0 : change, 1 : add

        Node(T val) : val(val), lazy(0), l(0), r(0), lazyKind(1) {}
        Node() : Node(0) {} // 항등원
    };

    T merge(const T &a, const T &b) { return a + b; }

    vector<Node> tree;
    const int root = 1;
    const idx_t MAX_IDX;

    int newNode() { tree.push_back(Node()); return tree.size() - 1; }

    void propagate(int node, int s, int e) {
        if (!node) return; // tree[0].val은 항상 항등원으로 유지되어야 함

        if (tree[node].lazyKind == 0) { // updateChange
            tree[node].val = (e - s + 1) * tree[node].lazy;
            if (s != e) {
                if (!tree[node].l) tree[node].l = newNode();
                tree[tree[node].l].lazyKind = 0;
                tree[tree[node].l].lazy = tree[node].lazy;
                if (!tree[node].r) tree[node].r = newNode();
                tree[tree[node].r].lazyKind = 0;
                tree[tree[node].r].lazy = tree[node].lazy;
            }
            tree[node].lazyKind = 1;
            tree[node].lazy = 0;
        }
        else { // updateAdd
            if (!tree[node].lazy) return;

            tree[node].val += (e - s + 1) * tree[node].lazy;
            if (s != e) {
                if (!tree[node].l) tree[node].l = newNode();
                tree[tree[node].l].lazy += tree[node].lazy;
                if (!tree[node].r) tree[node].r = newNode();
                tree[tree[node].r].lazy += tree[node].lazy;
            }
            tree[node].lazy = 0;
        }
    }

    bool haveOverlap(idx_t s, idx_t e, idx_t l, idx_t r) {
        return !(r < s || e < l);
    }

    // 항상 haveOverlap()으로 확인된 구간만 들어옴, 구간이 하나도 겹치지 않는 경우는 애초에 없음
    void update(int node, idx_t s, idx_t e, idx_t l, idx_t r, T val, bool add) {
        if (l <= s && e <= r) {
            if (!add) { // updateChange
                tree[node].lazyKind = 0;
                tree[node].lazy = val;
            }
            else tree[node].lazy += val;
            return;
        }
        else {
            idx_t m = s + e >> 1;
            if (haveOverlap(s, m, l, r)) {
                if(!tree[node].l) tree[node].l = newNode();
                update(tree[node].l, s, m, l, r, val, add);
            }
            if (haveOverlap(m + 1, e, l, r)) {
                if(!tree[node].r) tree[node].r = newNode();
                update(tree[node].r, m + 1, e, l, r, val, add);
            }

            propagate(tree[node].l, s, m);
            propagate(tree[node].r, m + 1, e);
            tree[node].val = tree[tree[node].l].val + tree[tree[node].r].val;
        }
    }

    T query(int node, idx_t s, idx_t e, idx_t l, idx_t r) {
        if (!node) return tree[0].val; // dummy
        propagate(node, s, e);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node].val;

        idx_t m = s + e >> 1;
        T lq = haveOverlap(s, m, l, r) ? query(tree[node].l, s, m, l, r) : tree[0].val;
        T rq = haveOverlap(m + 1, e, l, r) ? query(tree[node].r, m + 1, e, l, r) : tree[0].val;
        return merge(lq, rq);
    }

public:
    DynamicLazySeg(idx_t maxIdx) : MAX_IDX(maxIdx), tree(2) {} // tree[0] : dummy, tree[1] : root

    void reserve(int sz) { if (sz > tree.capacity()) tree.reserve(sz); } // array doubling 최소화

    void updateAdd(idx_t l, idx_t r, T val) { // 0 <= i <= MAX_IDX
        update(root, 0, MAX_IDX, l, r, val, 1);
    }

    void updateAdd(idx_t idx, T val) { // 0 <= i <= MAX_IDX
        update(root, 0, MAX_IDX, idx, idx, val, 1);
    }

    void updateChange(idx_t l, idx_t r, T val) { // 0 <= i <= MAX_IDX
        update(root, 0, MAX_IDX, l, r, val, 0);
    }

    void updateChange(idx_t idx, T val) { // 0 <= i <= MAX_IDX
        update(root, 0, MAX_IDX, idx, idx, val, 0);
    }

    T query(idx_t l, idx_t r) { // 0 <= l <= r <= MAX_IDX
        return query(root, 0, MAX_IDX, l, r);
    }

private:
    idx_t findKthSmallest(int node, idx_t s, idx_t e, T k) {
        if (s == e) return s;

        idx_t m = s + e >> 1;
        propagate(tree[node].l, s, m);
        T lsz = tree[tree[node].l].val;
        if (lsz >= k) return findKthSmallest(tree[node].l, s, m, k);
        return findKthSmallest(tree[node].r, m + 1, e, k - lsz);
    }

    idx_t findKthLargest(int node, idx_t s, idx_t e, T k) {
        if (s == e) return s;

        idx_t m = s + e >> 1;
        propagate(tree[node].r, m + 1, e);
        T rsz = tree[tree[node].r].val;
        if (rsz >= k) return findKthLargest(tree[node].r, m + 1, e, k);
        return findKthLargest(tree[node].l, s, m, k - rsz);
    }

public:
    idx_t findKthSmallest(int k) {
        assert (k >= 1);
        propagate(root, 0, MAX_IDX);
        return k > tree[root].val ? -1 : findKthSmallest(root, 0, MAX_IDX, k);
    }

    idx_t findKthLargest(int k) {
        assert (k >= 1);
        propagate(root, 0, MAX_IDX);
        return k > tree[root].val ? -1 : findKthLargest(root, 0, MAX_IDX, k);
    }
};
