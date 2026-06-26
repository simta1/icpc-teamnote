// {a_1, a_2, ..., a_n} 중 일부의 합으로 표현할 수 없는 최소의 수
template <typename T>
T smallestUnconstructibleValue(vector<T> v) {
    T pfs = 0;
    sort(v.begin(), v.end());
    for (auto e : v) {
        if (pfs + 1 < e) return pfs + 1;
        pfs += e;
    }
    return pfs + 1;
}