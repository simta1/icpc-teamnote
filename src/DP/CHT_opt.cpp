template <typename T>
struct CHT {
	struct Line { // y = ax + b (x >= s)
		T a, b;
		T getY(T x) { return a * x + b; }
	};

	vector<Line> lines;
	int n = 0; // lines[0:n-1]까지가 유효한 구간이라는 뜻
	vector<tuple<int, int, Line> > history; // {n, changedIdx, line before change}

	bool shouldKeep(int idx, const Line &line) { // intersect(lines[idx - 1], line) < intersect(lines[idx], line)
		return idx == 0 || hh(lines[idx - 1].b - line.b) * (line.a - lines[idx].a) < hh(lines[idx].b - line.b) * (line.a - lines[idx - 1].a);
	}

	bool check(int idx, T x) { // intersect(lines[idx - 1], lines[idx]) <= x
		return idx == 0 || (lines[idx].b - lines[idx - 1].b) <= x * hh(lines[idx - 1].a - lines[idx].a);
	}

	CHT() {}

	void add(T a, T b) {
		Line cur = {a, b};

		int lo = -1, hi = n;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (shouldKeep(mid, cur)) lo = mid;
			else hi = mid;
		}

		if (lo + 1 >= lines.size()) lines.emplace_back();
		history.emplace_back(n, lo + 1, lines[lo + 1]);
		lines[lo + 1] = cur;
		n = lo + 2;
	}

	void rollback() {
		auto [prevN, changedIdx, lineBeforeChange] = history.back();
		history.pop_back();
		n = prevN;
		lines[changedIdx] = lineBeforeChange;
	}

	T query(T x) {
		assert(n > 0);
		int lo = 0, hi = n;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (check(mid, x)) lo = mid;
			else hi = mid;
		}
		return lines[lo].getY(x);
	}
};
