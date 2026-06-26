template <typename Container> // Container = string or vector<>
vector<int> manacher(const Container &orig, typename Container::value_type dummy) { // O(N)
 // dummy는 Container에 없는 문자 -> ex) char이면 '#' 같은 거
    Container st(orig.size() << 1 | 1, dummy);
    for (int i = 0; i < orig.size(); i++) st[2 * i + 1] = orig[i];

    vector<int> r(st.size());
    for (int i = 1, p = 0; i < st.size(); i++) { // p는 0<=j<i인 j들 중 j + r[j]가 가장 큰 j
        r[i] = i > p + r[p] ? 0 : min(r[2 * p - i], p + r[p] - i);
        while (i - r[i] - 1 >= 0 && i + r[i] + 1 < st.size() && st[i - r[i] - 1] == st[i + r[i] + 1]) ++r[i];
        if (p + r[p] < i + r[i]) p = i;
    }
    return r;
} // st[i]를 중심으로 하는 가장 긴 팰린드롬 길이 : r[2i+1], st[i]와 st[i+1] 중심으로 하는 건 r[2i+2]
// i중심인 부분문자열 개수 (r[i] + 1) / 2

vector<int> getMaxEvenPalindromeStartingAt(int n, const vector<int> &r) { // O(N)
    vector<int> res(n);
    for (int i = 0; i < n - 1; i++) {
        int len = r[2 * i + 2]; // len짝수임
        res[i - (len / 2) + 1] = max(res[i - (len / 2) + 1], len);
    }
    for (int i = 1; i < n; i++) res[i] = max(res[i], res[i - 1] - 2);
    return res;
}
vector<int> getMinEvenPalindromeStartingAt(int n, const vector<int> &r) { // O(N alpha(N))
    vector<int> res(n, -1);
    DSU dsu(n + 1);
    for (int i = 0; i + 1 < n; i++) {
        int len = r[2 * i + 2];
        if (len == 0) continue;
        for (int x = dsu.find(i - len / 2 + 1); x <= i; x = dsu.find(x)) {
            res[x] = 2 * (i - x + 1);
            dsu.p[x] = dsu.find(x + 1);
        }
    }
    return res;
}