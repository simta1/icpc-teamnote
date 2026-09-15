auto getCartesian(const vector<int> &v) { // min // 0-based
    int n = v.size();
    vector<pair<int, int>> chd(n, {-1, -1});
    vector<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && v[s.back()] > v[i]) {
            chd[i].first = s.back();
            s.pop_back();
        }
        if (!s.empty()) chd[s.back()].second = i;
        s.push_back(i);
    }
    return pair{s[0], chd}; // root, chd
}
// i의 왼쪽 직계 자식에서 오른쪽 방향으로만 이동하는 체인 위의 j에 대해 right_lt[j]=i
// i의 오른쪽 직계 자식에서 왼쪽 방향으로만 이동하는 체인 위의 j에 대해 left_le[j]=i