template <typename T, const T& (*op)(const T&, const T&)>
struct RMQ {
	vector<vector<T> > ac; // ac[i][j] = op(v[j:j+2^i))
	RMQ(const vector<T> &v) : ac(1, v) { // O(N logN)
		for (int i = 1, len = 1; len * 2 <= v.size(); ++i, len *= 2) {
			ac.emplace_back(v.size() - len * 2 + 1);
			for (int j = 0; j < ac[i].size(); j++) ac[i][j] = op(ac[i - 1][j], ac[i - 1][j + len]);
		}
	}
	T query(int a, int b) const { // 0-based // op[a:b]의 op() 누적값 // O(1)
		assert(0 <= a && a <= b && b < ac[0].size());
		int i = __lg(b - a + 1);
		return op(ac[i][a], ac[i][b - (1 << i) + 1]);
	}
};
// const RMQ<int, min> rmq(v);