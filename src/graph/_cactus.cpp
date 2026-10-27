pair<bool, bool> isCactus(int n, const vector<vector<pair<int, int> > > &bccs, const vector<pair<int, int>> &edges) { // O(V + E)
    vector<int> cnt(n + 1);
    for (auto &bcc : bccs) {
        auto nodes = getNodeOfBCC(n, bcc, edges);
        int E = bcc.size(), V = nodes.size();
        if (E < V) continue;
        if (E > V) return {false, false};
        for (auto node : nodes) ++cnt[node];
    }
    bool isEdgeCactus = true, isVertexCactus = true;
    for (auto e : cnt) if (e >= 2) isVertexCactus = false;
    return {isEdgeCactus, isVertexCactus};
}
