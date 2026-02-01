template <typename T>
class MergesortTree {
private:
    int n;
    vector<vector<T> > tree;

    int count(const vector<T> &v, int k) {
        // ex)
        // return upper_bound(v.begin(), v.end(), k) - v.begin();
    }

    void init(const vector<T> &v, int node, int s, int e) {
        if (s == e) {
            tree[node].push_back(v[s]);
            return;
        }

        int m = s + e >> 1;
        init(v, node * 2, s, m);
        init(v, node * 2 + 1, m + 1, e);
        tree[node].resize(tree[node * 2].size() + tree[node * 2 + 1].size());
        merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), tree[node].begin());
    }

    int query(int node, int s, int e, int l, int r, int k) {
        if (l <= s && e <= r) return count(tree[node], k);
        if (r < s || e < l) return 0;

        int m = s + e >> 1;
        return query(node * 2, s, m, l, r, k) + query(node * 2 + 1, m + 1, e, l, r, k);
    }

public:
    MergesortTree(const vector<T> &v) : n(v.size()), tree(4 * v.size()) {
        init(v, 1, 0, n - 1);
    }

    int query(int l, int r, int k) { // 1-based
        return query(1, 0, n - 1, l - 1, r - 1, k);
    }
};
// time, space O(N~logN)