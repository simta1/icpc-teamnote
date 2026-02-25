template <bool onlyPositive, typename T>
void radixSort(vector<T> &v) { // int O(4N), long long O(8N)
    static_assert(is_integral<T>::value, "T must be integer");

    const unsigned int SZ = 8;
    const unsigned int mask = (1 << SZ) - 1;
    static queue<T> qs[1 << SZ];

    for (int k = 0; k < sizeof(T); k++) {
        for (const auto &e : v) qs[e >> k * SZ & mask].push(e);
        v.clear();

        for (auto& q : qs) {
            while (q.size()) {
                v.push_back(q.front());
                q.pop();
            }
        }
    }

    if constexpr (!onlyPositive) {
        for (int i = 0; i < v.size(); i++) if (v[i] < 0) {
            rotate(v.begin(), v.begin() + i, v.end());
            break;
        }
    }
}