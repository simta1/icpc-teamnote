template <typename T, int D>
struct FenwickTree {
    vector<FenwickTree<T, D - 1> > tree;

    template <typename... Args>
    FenwickTree(int n, Args... args) : tree(n + 1, FenwickTree<T, D - 1>(args...)) {}

    template <typename... Args>
    void update(int pos, Args... args) {
        for (; pos < tree.size(); pos += (pos & -pos)) tree[pos].update(args...);
    }

    template <typename... Args>
    T sum(int r, Args... args) const {
        T res = 0;
        for (; r; r -= (r & -r)) res += tree[r].query(args...);
        return res;
    }

    template <typename... Args>
    T query(int l, int r, Args... args) const {
        return sum(r, args...) - sum(l - 1, args...);
    }
};

template <typename T>
struct FenwickTree<T, 0> {
	T val = 0;
	void update(T v) { val += v; }
	T query() const { return val; }
};

// ex) 3D fenwick
// FenwickTree<int, 3> fw(n, m, k);
// fw.update(x, y, z, add); // O(logN logM logK)
// fw.query(x1, x2, y1, y2, z1, z2); // O(logN logM logK)
