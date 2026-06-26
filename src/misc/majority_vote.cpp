template <typename T>
pair<bool, T> boyerMoore(const vector<T> &v) { // O(N)
    assert(!v.empty());
    int cnt = 0;
    T candi;
    for (auto e : v) {
        if (!cnt) candi = e;
        if (e == candi) ++cnt;
        else --cnt;
    }
    if (cnt) {
        cnt = 0;
        for (auto e : v) cnt += (e == candi);
    }
    return {cnt > v.size() / 2, candi};
}