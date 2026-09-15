constexpr ld eps = 1e-5;
ld dnc(vector<pair<ll, ll>> v) { // O(N log^2N)
    assert(v.size() > 1);
    sort(v.begin(), v.end(), [&](auto &a, auto &b) { return a.first < b.first; });
    auto f = [&](auto &&f, int s, int e) -> ld {
        if (s + 1 == e) return dist(v[s], v[e]);
        if (s + 2 == e) return min({
            dist(v[s], v[s + 1]),
            dist(v[s + 1], v[e]),
            dist(v[e], v[s])
        });
        int m = s + e >> 1;
        ld res = min(f(f, s, m), f(f, m + 1, e));
        vector<pair<ll, ll>> mids;
        for (int i = s; i <= e; i++) {
            if (abs(v[m].first - v[i].first) < res) mids.push_back(v[i]);
        }
        // TLE나면 merge사용
        sort(mids.begin(), mids.end(), [&](auto &a, auto &b) { return a.second < b.second; });
        for (int i = 0; i < mids.size() - 1; i++) {
            for (int j = i + 1; j < mids.size(); j++) {
                if (mids[j].second - mids[i].second >= res) break;
                res = min(res, dist(mids[i], mids[j]));
            }
        }
        return res;
    };
    return f(f, 0, v.size() - 1);
}