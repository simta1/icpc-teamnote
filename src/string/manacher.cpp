template <typename Container>
vector<int> manacher(const Container &orig, typename Container::value_type dummy) { // O(N)
	Container st(orig.size() << 1 | 1, dummy);
	for (int i = 0; i < orig.size(); i++) st[2 * i + 1] = orig[i];
	vector<int> r(st.size());
	for (int i = 1, p = 0; i < st.size(); i++) {
		if (i < p + r[p]) r[i] = min(p + r[p] - i, r[2 * p - i]);
		while (i - r[i] - 1 >= 0 && i + r[i] + 1 < st.size() && st[i - r[i] - 1] == st[i + r[i] + 1]) ++r[i];
		if (p + r[p] < i + r[i]) p = i;
	}
	return r;
} // 중심st[i]인 가장 긴 팰린드롬 길이 : r[2i+1], 중심st[i:i+1] : r[2i+2]