vector<int> getMaxEvenPalindromeStartingAt(int n, const vector<int> &r) { // O(N)
	vector<int> res(n);
	for (int i = 0; i < n - 1; i++) {
		int len = r[2 * i + 2]; // len짝수임
		res[i - (len / 2) + 1] = max(res[i - (len / 2) + 1], len);
	}
	for (int i = 1; i < n; i++) res[i] = max(res[i], res[i - 1] - 2);
	return res;
}
vector<int> getMinEvenPalindromeStartingAt(int n, const vector<int> &r) { // O(N alpha(N))
	vector<int> res(n, -1);
	DSU dsu(n + 1);
	for (int i = 0; i + 1 < n; i++) {
		int len = r[2 * i + 2];
		if (len == 0) continue;
		for (int x = dsu.find(i - len / 2 + 1); x <= i; x = dsu.find(x)) {
			res[x] = 2 * (i - x + 1);
			dsu.p[x] = dsu.find(x + 1);
		}
	}
	return res;
}
