template <typename T>
int LIS(const vector<T> &v) {
	vector<T> dp;
	for (auto e : v) {
		if (dp.empty() || dp.back() < e) dp.push_back(e);
		else *lower_bound(dp.begin(), dp.end(), e) = e;
	}
	return dp.size();
}

template <typename T>
vector<int> LIS(const vector<T> &v) {
	int n = v.size();
	vector<int> pos(n);
	vector<T> dp;
	for (int i = 0; i < n; i++) {
		if (dp.empty() || dp.back() < v[i]) {
			pos[i] = dp.size();
			dp.push_back(v[i]);
		}
		else {
			pos[i] = lower_bound(dp.begin(), dp.end(), v[i]) - dp.begin();
			dp[pos[i]] = v[i];
		}
	}
	vector<int> LIS(dp.size());
	for (int i = n - 1, cur = dp.size() - 1; i >= 0; i--) if (pos[i] == cur) LIS[cur--] = i;
	return LIS;
}