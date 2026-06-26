// O((N+M)\log(N+M)) LCS
template <typename Container> // Container = string or vector<>
Container LCString(const Container &a, const Container &b, typename Container::value_type dummy) {
    Container st(a.size() + 1 + b.size(), dummy);
    for (int i = 0; i < a.size(); i++) st[i] = a[i];
    for (int i = 0; i < b.size(); i++) st[a.size() + 1 + i] = b[i];
    auto [sa, rank] = getSuffixArray(st);
    auto lcp = getLCPArray(st, sa, rank);
    int idx = -1, len = 0;
    for (int i = 0; i < lcp.size(); i++) if ((int(a.size() - sa[i]) ^ int(a.size() - sa[i + 1])) < 0) { // sa[i]<a.size()<sa[i+1] or sa[i+1]<a.size()<sa[i]
        if (len < lcp[i]) {
            len = lcp[i];
            idx = i;
        }
    }
    if (!~idx) return Container(0, 0);
    return Container(st.begin() + sa[idx], st.begin() + sa[idx] + lcp[idx]);
}

// 가장 긴 반복 부분 문자열
template <typename Container> // Container = string or vector<>
Container longestRepeatedSubstring(const Container &st, const vector<int> &sa, const vector<int> &lcp) {
    if (st.size() == 1) return Container(0, 0);
    int i = max_element(lcp.begin(), lcp.end()) - lcp.begin();
    return Container(st.begin() + sa[i], st.begin() + sa[i] + lcp[i]);
}

// 서로 다른 부분 문자열의 개수
long long countDistinctSubstrings(const string &st, const vector<int> &lcp) {
    long long n = st.size();
    return n * (n + 1) / 2 - accumulate(lcp.begin(), lcp.end(), 0LL);
}

// k번 이상 등장하는 서로 다른 부분 문자열의 개수, k번 이상 등장하는 가장 긴 부분 문자열
vector<int> dequeTrickMin(int len, const vector<int> &v) { // res[i]는 v[max(0, i - len + 1)]~v[i]의 최솟값 // 즉, 정확히 길이가 len인 구간의 최솟값은 res[len-1:n)에 저장됨
    vector<int> res(v.size());
    deque<int> dq;
    for (int i = 0; i < v.size(); i++) {
        while (!dq.empty() && v[dq.back()] > v[i]) dq.pop_back();
        dq.push_back(i);
        if (i - dq.front() + 1 > len) dq.pop_front();
        res[i] = v[dq.front()];
    }
    return res;
}

long long countDistinctSubstringsRepeatedAtLeastK(const vector<int> &lcp, int k) { // k번 이상 등장하는 반복 부분 문자열 종류의 수
    assert(k >= 2); // k=1일 땐  n * (n + 1) / 2 - accumulate(lcp.begin(), lcp.end(), 0LL);
    if (lcp.size() + 1 < k) return 0; // 문자열 길이는 lcp.size()+1
    auto rmq = dequeTrickMin(k - 1, lcp); // sa배열 k개의 최장공통접두사가 필요하므로 lcp배열에선 k-1개씩 뽑아서 min값을 구하면 됨
    long long res = rmq[k - 2];
    for (int i = k - 1; i < lcp.size(); i++) res += max(0, rmq[i] - rmq[i - 1]);
    return res;
}

template <typename Container> // Container = string or vector<>
Container longestSubstringRepeatedAtLeastK(const Container &st, const vector<int> &sa, const vector<int> &lcp, int k) { // k번 이상 등장하는 부분 문자열 중 가장 긴 부분 문자열
    if (k == 1) return st;
    if (st.size() < k) return Container(0, 0);
    auto rmq = dequeTrickMin(k - 1, lcp); // sa배열 k개의 최장공통접두사가 필요하므로 lcp배열에선 k-1개씩 뽑아서 min값을 구하면 됨
    int i = max_element(rmq.begin() + k - 2, rmq.end()) - rmq.begin();
    return Container(st.begin() + sa[i], st.begin() + sa[i] + rmq[i]);
}
