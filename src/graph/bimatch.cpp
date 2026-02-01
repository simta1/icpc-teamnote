// addEdge(l, r) : adj[l].push_back(r); // 0<=l<n1, 0<=r<n2
tuple<int, vector<int>, vector<int> > bimatch(int n1, int n2, const vector<vector<int> > &adj) { // O(VE) // 0-based
    vector<int> matchL(n1, -1), matchR(n2, -1), checkedR(n2, 0);
    auto dfs = [&](auto &&dfs, int l, int trueValue) -> bool {
        for (auto r : adj[l]) if (checkedR[r] != trueValue) {
            checkedR[r] = trueValue;
            if (!~matchR[r] || dfs(dfs, matchR[r], trueValue)) {
                matchL[l] = r;
                matchR[r] = l;
                return true;
            }
        }
        return false;
    };
    int res = 0;
    for (int i = 0; i < adj.size(); i++) res += dfs(dfs, i, i + 1);
    return {res, matchL, matchR};
}
pair<vector<int>, vector<int> > getMVC(int n1, int n2, const vector<vector<int> > &adj, const vector<int> &matchL, const vector<int> &matchR) { // O(V+E) // 0-based
    vector<bool> visitedL(n1), visitedR(n2);
    auto dfs = [&](auto &&dfs, int l) -> void {
        visitedL[l] = true;
        for (auto r : adj[l]) if (~matchR[r] && !visitedR[r] && !visitedL[matchR[r]]) {
            visitedR[r] = true;
            dfs(dfs, matchR[r]);
        }
    };
    for (int l = 0; l < n1; l++) if (!~matchL[l]) dfs(dfs, l);
    vector<int> mvcL, mvcR;
    for (int l = 0; l < n1; l++) if (!visitedL[l]) mvcL.push_back(l);
    for (int r = 0; r < n2; r++) if (visitedR[r]) mvcR.push_back(r);
    return {mvcL, mvcR};
}