template <typename T, int D>
struct FenwickTree {
	vector<FenwickTree<T, D - 1>> tree;
	template <typename... Args>
	FenwickTree(int n, Args... args) : tree(n + 1, FenwickTree<T, D - 1>(args...)) {}
	template <typename... Args>
	void upd(int pos, Args... args) {
		for (; pos < tree.size(); pos += (pos & -pos)) tree[pos].upd(args...);
	}
	template <typename... Args>
	T sum(int r, Args... args) const {
		T res = 0;
		for (; r; r -= (r & -r)) res += tree[r].qry(args...);
		return res;
	}
	template <typename... Args>
	T qry(int l, int r, Args... args) const {
		return sum(r, args...) - sum(l - 1, args...);
	}
};
template <typename T>
struct FenwickTree<T, 0> {
	T val = 0;
	void upd(T v) { val += v; }
	T qry() const { return val; }
};
// ex) 3D fenwick
// FenwickTree<int, 3> fw(n, m, k);
// fw.upd(x, y, z, add); // O(logN logM logK)
// fw.qry(x1, x2, y1, y2, z1, z2); // O(logN logM logK)
