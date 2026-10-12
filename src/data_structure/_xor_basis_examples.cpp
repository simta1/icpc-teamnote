int qry(vector<int> basis, int a, int b) {
	sort(basis.rbegin(), basis.rend());
	for (int i = 1; i < basis.size(); i++) {
		int bit = 1 << __lg(basis[i]);
		for (int j = 0; j < i; j++) {
			if (basis[j] & bit) basis[j] ^= basis[i];
		}
	}
	int mx = 0;
	for (auto e : basis) if ((mx ^ e) <= b) mx ^= e;
	return mx >= a ? mx : -1;
}

void rollback(vector<int> &basis, int sz) {
	basis.resize(sz);
}
