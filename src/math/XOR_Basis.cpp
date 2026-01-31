template <typename T>
vector<T> getXorBasis(const vector<T> &v) {
    vector<T> basis;
    for (auto e : v) {
        for (auto b : basis) e = min(e, e ^ b);
        if (e) basis.push_back(e);
    }
    sort(basis.rbegin(), basis.rend());
    return basis;
}
// T max_xor_sum = 0;
// for (auto b : getXorBasis(v)) max_xor_sum = max(max_xor_sum, max_xor_sum ^ b);