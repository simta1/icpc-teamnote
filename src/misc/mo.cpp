template <typename T>
vector<T> mo(const vector<int> &v, const vector<pair<int, int>> &_qs) { // O((N+Q)sqrt(N)T(N)) // T(N)은 push(), pop()의 시간복잡도   
    int q = _qs.size();
    assert(q);
    struct Query { int s, e, idx; };
    vector<Query> qs(q); // {s, e, idx}
    vector<T> res(q);
    for (int i = 0; i < q; i++) qs[i] = {_qs[i].first, _qs[i].second, i};
    int sqr = sqrt(v.size()) + 1;
    sort(qs.begin(), qs.end(), [&sqr](auto &a, auto &b) {
        if (a.s / sqr != b.s / sqr) return a.s < b.s;
        return (a.s / sqr) & 1 ? a.e > b.e : a.e < b.e;
    });
    auto push_back = [&](int idx) {};
    auto pop_back = [&](int idx) {};
    auto push_front = push_back;
    auto pop_front = pop_back;
    auto query = [&]() -> T {};
    auto [cs, ce, idx] = qs[0];
    for (int i = cs; i <= ce; i++) push_back(i);
    res[idx] = query();
    for (int i = 1; i < qs.size(); i++) {
        auto [s, e, idx] = qs[i];
        while (cs > s) push_front(--cs);
        while (ce < e) push_back(++ce);
        while (cs < s) pop_front(cs++);
        while (ce > e) pop_back(ce--);
        res[idx] = query();
    }
    return res;
}
