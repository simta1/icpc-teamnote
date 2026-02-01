template <typename T>
class FenwickTree {
private:
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}
    FenwickTree(const vector<T> &v) : tree(v.size() + 1) {
        for (int i = 0; i < v.size(); i++) updateAdd(i + 1, v[i]);
    }

    void updateAdd(int i, T val) { // 1-based // O(logN)
        for (; i < tree.size(); i += (i & -i)) tree[i] += val;
    }

    void updateChange(int i, T val) { // 1-based // O(logN)
        updateAdd(i, val - query(i, i));
    }

    T query(int l, int r) { // 1-based // O(logN)
        T res = 0;
        for (int i = r; i > 0; i -= (i & -i)) res += tree[i];
        for (int i = l - 1; i > 0; i -= (i & -i)) res -= tree[i];
        return res;
    }
};