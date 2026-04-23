template <typename T>
T kadane(const vector<T> &v) { // O(N)
    T res = v[0], sum = 0;
    for (auto &e : v) {
        sum = max(sum, 0) + e;
        res = max(res, sum);
    }
    return res; // 최소한 하나 이상 골라야 할 때
    return max(res, 0); // 아무것도 안 골라도 될 때
}