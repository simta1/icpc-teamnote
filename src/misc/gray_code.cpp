void grayCode(int n) {
	for (int i = 0; i < (1 << n); ++i) cout << (i ^ (i >> 1)) << "\n";
}