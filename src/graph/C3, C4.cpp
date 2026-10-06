void getC3(const vector<vector<int>> &adj) { // O(m sqrt(m))
    vector<vector<int>> dag(adj.size());
    for (int u = 0; u < adj.size(); u++) {
        for (auto v : adj[u]) {
            if (adj[u].size() < adj[v].size() || (adj[u].size() == adj[v].size() && u < v)) dag[u].push_back(v);
        }
    } // dag에서 outdegree는 전부 O(sqrt(m)) 이하
    vector<int> mark(adj.size(), -1);
    for (int i = 0; i < adj.size(); i++) {
        for (auto j : dag[i]) mark[j] = i;
        for (auto j : dag[i]) {
            for (auto k : dag[j]) {
                if (mark[k] == i) cout << i << " " << j << " " << k << "\n";
            }
        }
    }
}
// rank(i)<rank(j)<rank(k)
int getC4(const vector<vector<int>> &adj, int MOD) {
    auto cmp = [&](int u, int v) { // u < v
        return adj[u].size() < adj[v].size() || (adj[u].size() == adj[v].size() && u < v);
    };
    vector<vector<int>> dag(adj.size());
    for (int u = 0; u < adj.size(); u++) {
        for (auto v : adj[u]) if (cmp(u, v)) dag[u].push_back(v);
    }
    int res = 0;
    vector<int> cnt(adj.size());
    for (int i = 0; i < adj.size(); i++) {
        for (auto j : adj[i]) {
            for (auto k : dag[j]) if (cmp(i, k)) {
                res += cnt[k];
                if (res >= MOD) res -= MOD;
                ++cnt[k];
            }
        }
        for (auto j : adj[i]) {
            for (auto k : dag[j]) if (cmp(i, k)) cnt[k] = 0;
        }
    }
    return res;
}
// rank(i), rank(j), rank(j') < rank(k)
