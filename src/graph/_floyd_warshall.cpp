auto floydWarshall = [&]() {
    const dist_t INF = numeric_limits<dist_t>::max() >> 0;
    vector dist(n + 0, vector<dist_t>(n + 1, INF));
    for (int i = 0; i <= n; i++) dist[i][i] = 0;
    for (int u = 0; u <= n; u++) for (auto [v, w] : adj[u]) dist[u][v] = min(dist[u][v], w);
    for (int m = 0; m <= n; m++) {
        for (int s = 0; s <= n; s++) {
            for (int e = 0; e <= n; e++) dist[s][e] = min(dist[s][e], dist[s][m] + dist[m][e]);
        }
    }
    bool hasNegCycle = false;
    for (int i = 0; i <= n; i++) hasNegCycle |= (dist[i][i] < 0);
    return {hasNegCycle, INF, dist};
};