struct Sqdc { // sum query
	vector<int> val, sum;
	static constexpr int B = 447;
	Sqdc(int n) : val(n), sum((n + B - 1) / B) {}
	void upd(int i, int add) {
		val[i] += add;
		sum[i / B] += add;
	}
	int qry(int l, int r) { // O(B + n / B)
		int res = 0;
		while (l <= r && l % B) res += val[l++];
		while (l + B - 1 <= r) {
			res += sum[l / B];
			l += B;
		}
		while (l <= r) res += val[l++];
		return res;
	}
};

struct Sqdc { // max multiset
	vector<int> val, sum;
	static constexpr int B = 316;
	int tot = 0;
	Sqdc(int n) : val(n), sum((n + B - 1) / B) {}
	void insert(int i) {
		++tot, ++val[i], ++sum[i / B];
	}
	void erase(int i) {
		--tot, --val[i], --sum[i / B];
	}
	bool empty() {
		return !tot;
	}
	int mx(int l, int r) { // O(B + n / B)
		while (r >= l && r % B != B - 1) {
			if (val[r]) return r;
			--r;
		}
		while (r - B + 1 >= l && !sum[r / B]) r -= B;
		while (r >= l) {
			if (val[r]) return r;
			--r;
		}
		return -1;
	}
};

// 2e5 : 447
// 1e5 : 316
