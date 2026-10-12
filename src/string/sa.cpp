template <typename Container>
auto get_sa(const Container &st) { // O(N logN)
	int n = st.size();
	if (n == 1) return pair{vector{0}, vector{0}};
	assert(n > 0);
	int m = *max_element(st.begin(), st.end());
	vector<int> sa(n), x(n + 1), y(n + 1), cnt(max(n, m) + 1);
	for (int i = 0; i < n; i++) assert(st[i] > 0);
	for (int i = 0; i < n; i++) ++cnt[x[i] = st[i]];
	for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--) sa[--cnt[x[i]]] = i;
	for (int len = 1, p = 1; p < n; len <<= 1, m = p) {
		int idx = 0;
		for (int i = n - len; i < n; i++) y[idx++] = i;
		for (int i = 0; i < n; i++) if (sa[i] >= len) y[idx++] = sa[i] - len;
		fill(cnt.begin(), cnt.begin() + m + 1, 0);
		for (int i = 0; i < n; i++) ++cnt[x[y[i]]];
		for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
		swap(x, y);
		x[sa[0]] = p = 1;
		for (int i = 1; i < n; i++) {
			int a = sa[i - 1], b = sa[i];
			x[b] = y[a] == y[b] && y[a + len] == y[b + len] ? p : ++p;
		}
	}
	x.resize(n);
	for (auto &e : x) --e;
	return pair{sa, x}; // rank=x
}
template <typename Container>
vector<int> get_lcp(const Container &st, const vector<int> &sa, const vector<int> &rank) { // O(N)
	int n = st.size();
	assert(n >= 1);
	vector<int> lcp(n - 1);
	for (int i = 0, h = 0; i < n; ++i, h -= !!h) if (rank[i]) {
		for (int j = sa[rank[i] - 1]; j + h < n && i + h < n && st[j + h] == st[i + h];) ++h;
		lcp[rank[i] - 1] = h;
	}
	return lcp;
} // lcp[i]: sa[i], sa[i + 1]의 최장 공통 접두사 // lcp.size() = n-1
// auto [sa, rank] = get_sa(st);
// auto lcp = get_lcp(st, sa, rank);
// RMQ<int, min> rmq(lcp);
auto lce = [&](int i, int j) { // lcp(st[i:], st[j:])
	if (i == j) return n - i;
	int idx1 = rank[i];
	int idx2 = rank[j];
	if (idx1 > idx2) swap(idx1, idx2);
	return rmq.query(idx1, idx2 - 1); // i!=j라서 idx1 <= idx2 - 1 성립
};
auto cmp = [&](int i, int j, int i2, int j2) { // st[i:j] < st[i2:j2]
	int len = lce(i, i2);
	if (len >= min(j - i + 1, j2 - i2 + 1)) return j - i < j2 - i2;
	return rank[i] < rank[i2];
};
