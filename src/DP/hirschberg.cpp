vector<int> getDP(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<int> dp(m + 1);
    for (int i = 1; i <= n; i++) {
        vector<int> ndp(m + 1);
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) ndp[j] = dp[j - 1] + 1;
            else ndp[j] = max(ndp[j - 1], dp[j]);
        }
        swap(dp, ndp);
    }
    return dp;
}

string LCS(const string &a, const string &b) { // time O(NM), space O(M)
    if (a.empty()) return "";
    if (a.size() == 1) return b.find(a) != string::npos ? a : "";
    int n = a.size(), m = b.size();
    int mid = n / 2;
    string l = a.substr(0, mid), r = a.substr(mid);
    auto dp1 = getDP(l, b);
    string rrev = r, brev = b;
    reverse(rrev.begin(), rrev.end());
    reverse(brev.begin(), brev.end());
    auto dp2 = getDP(rrev, brev);
    int mx = -1, mxIdx;
    for (int i = 0; i <= m; i++) {
        if (mx < dp1[i] + dp2[m - i]) {
            mx = dp1[i] + dp2[m - i];
            mxIdx = i;
        }
    }
    return LCS(l, b.substr(0, mxIdx)) + LCS(r, b.substr(mxIdx));
}