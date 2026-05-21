pair<int, vector<pair<int, int> > > getCartesian(const vector<int> &v) { // min // 0-based
    int n = v.size();
    vector<pair<int, int> > chd(n, {-1, -1});
    vector<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && v[s.back()] > v[i]) {
            chd[i].first = s.back();
            s.pop_back();
        }
        if (!s.empty()) chd[s.back()].second = i;
        s.push_back(i);
    }
    return {s[0], chd}; // root, chd
}