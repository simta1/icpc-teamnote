// compress
sort(nodes.begin(), nodes.end(), [&](int a, int b) {
    return dfsn[a] < dfsn[b];
});
int tmp = nodes.size();
for (int i = 1; i < tmp; i++) nodes.push_back(getLCA(nodes[i - 1], nodes[i]));
sort(nodes.begin(), nodes.end(), [&](int a, int b) {
    return dfsn[a] < dfsn[b];
});
nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
root = nodes[0];
for (int i = 1; i < nodes.size(); i++) {
    int u = getLCA(nodes[i - 1], nodes[i]);
    int v = nodes[i];
    chd[u].emplace_back(v, dist[v] - dist[u]);
}

// clean-up // O(sum(nodes.size()))
for (auto x : nodes) {
    chd[x].clear();
}
