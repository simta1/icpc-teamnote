template <typename T>
struct CHT {
    struct Line { // y = ax + b (x >= s)
        T a, b;
        double s;

        T getY(T x) {
            return a * x + b;
        }
    };

    double intersect(const Line &l1, const Line &l2) {
        assert(l1.a != l2.a);
        return double(l2.b - l1.b) / (l1.a - l2.a);
    }

    vector<Line> lines;
    int idx = 0;

    CHT() {}

    void add(T a, T b) {
        Line cur = {a, b, 0};
        while (!lines.empty()) {
            cur.s = intersect(cur, lines.back());
            if (cur.s <= lines.back().s) lines.pop_back();
            else break;
        }
        lines.push_back(cur);
        idx = min(idx, int(lines.size() - 1));
    }

    T fastQuery(T x) {
        while (idx + 1 < lines.size() && lines[idx + 1].s <= x) ++idx;
        return lines[idx].getY(x);
    }

    T query(T x) {
        int idx = upper_bound(lines.begin(), lines.end(), x, [](double x, const Line &f) {
            return x < f.s;
        }) - lines.begin() - 1;
        return lines[idx].getY(x);
    }
};

vector<ll> dp(n);
CHT<ll> cht;
// dp[i] = min_{j < i} [ slope(j) * x(i) + yIntercept(j) ]
// slope(j)가 단조 감소해야 사용할 수 있음

// x(i)값이 단조증가한다면 CHT::fastQuery() 사용   
// x(i)값이 불규칙하게 바뀌는 경우 CHT::query() 사용

auto x = [&](int i) { return _; };
auto slope = [&](int j) { return _; };
auto yIntercept = [&](int j) { return _; };
dp[0] = _;
for (int i = 1; i < n; i++) { // query O(NlogN), fastQuery O(N)
    cht.add(slope(i - 1), yIntercept(i - 1));
    dp[i] = cht.query(x(i));
}
cout << dp.back();