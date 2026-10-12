template <typename Container>
vector<int> get_z(const Container &st) { // O(N)
	vector<int> z(st.size());
	for (int i = 1, p = 0; i < st.size(); i++) {
		if (i < p + z[p]) z[i] = min(p + z[p] - i, z[i - p]);
		while (i + z[i] < st.size() && st[z[i]] == st[i + z[i]]) ++z[i];
		if (p + z[p] < i + z[i]) p = i;
	}
	z[0] = st.size();
	return z;
} // z[i] = lcp(st, st[i:])