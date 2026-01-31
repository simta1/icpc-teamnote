template <typename U, typename T>
class DynamicSeg {
private:
    struct Node {
        T val;
        int l, r;

        Node(T val) : val(val), l(0), r(0) {}
        Node() : Node(0) {}
    };

    int newNode() {
        tree.push_back(Node());
        return tree.size() - 1;
    }

    T merge(const T &a, const T &b) {
        return a + b;
    }

    const int root = 1;
    vector<Node> tree;
    const U MAX_IDX;

    void update(int node, U s, U e, U i, T val, bool add){
        if(s == e) {
            tree[node].val = val + add * tree[node].val;
            return;
        }

        U m = s + e >> 1;
        if (i <= m){
            if(!tree[node].l) tree[node].l = newNode();
            update(tree[node].l, s, m, i, val, add);
        }
        else {
            if(!tree[node].r) tree[node].r = newNode();
            update(tree[node].r, m + 1, e, i, val, add);
        }

        T lval = tree[node].l ? tree[tree[node].l].val : 0;
        T rval = tree[node].r ? tree[tree[node].r].val : 0;
        tree[node].val = merge(lval, rval);
    }

    T query(int node, U s, U e, U l, U r){
        if(!node) return 0;
        if(l <= s && e <= r) return tree[node].val;
        if(l > e || s > r) return 0;

        U m = s + e >> 1;
        T lq = query(tree[node].l, s, m, l, r);
        T rq = query(tree[node].r, m + 1, e, l, r);
        return merge(lq, rq);
    }

    U kth(int node, U s, U e, T k) {
        if (s == e) return e;
        U m = s + e >> 1;
        T lsz = tree[node].l ? tree[tree[node].l].val : 0;
        if (k <= lsz) return kth(tree[node].l, s, m, k);
        return kth(tree[node].r, m + 1, e, k - lsz);
    }

public:
    DynamicSeg(U maxIdx) : MAX_IDX(maxIdx), tree(2) {} // tree[0] : dummy, tree[1] : root
    
    void updateAdd(U i, T val) { // 0-based
        update(root, 0, MAX_IDX, i, val, 1);
    }

    void updateChange(U i, T val) { // 0-based
        update(root, 0, MAX_IDX, i, val, 0);
    }

    T query(U l, U r) { // 0-based
        return query(root, 0, MAX_IDX, l, r);
    }

    U kth(int k) {
        return kth(root, 0, MAX_IDX, k);
    }
};

/* space O(Q~logN) */
