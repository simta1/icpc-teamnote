template <typename T>
T dmst(int root, int n, vector<tuple<int, int, T>> &edges) {
	vector<int> comp(n + 1); // compressed
	vector<pair<int, T> > minIn(n + 1);
	const T INF = numeric_limits<T>::max();
	T res = 0;
	int curN = n;
	while (1) {
		fill(minIn.begin(), minIn.end(), pair<int, T>{-1, INF});
		for (auto &[cur, next, cost] : edges) if (cur != next) {
			if (minIn[next].second > cost) minIn[next] = {cur, cost};
		}
		minIn[root] = {-1, 0};
		for (int i = 1; i <= curN; i++) res += minIn[i].second;
		int nextN = 0;
		fill(comp.begin(), comp.end(), -1);
		comp[root] = ++nextN;
		for (int i = 1; i <= curN; i++) if (!~comp[i]) {
			int cur;
			for (cur = i; !~comp[cur]; cur = minIn[cur].first) comp[cur] = 0;
			if (!comp[cur]) {
				++nextN;
				for (; !comp[cur]; cur = minIn[cur].first) comp[cur] = nextN;
			}
			for (cur = i; !comp[cur]; cur = minIn[cur].first) comp[cur] = ++nextN;
		}
		if (curN == nextN) break;
		curN = nextN;
		for (auto &[cur, next, cost] : edges) {
			cost -= minIn[next].second;
			cur = comp[cur];
			next = comp[next];
		}
		root = comp[root];
	}
	return res;
}
