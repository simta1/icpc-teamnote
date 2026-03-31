auto mst = [&]() { // O(E logE)
    DSU dsu(n);
    priority_queue<tuple<int, int, int> > pq;
    for (int u = 1; u <= n; u++) {
        for (auto [v, w] : adj[u]) pq.emplace(-w, u, v);
    }
    while (!pq.empty()) {
        auto [w, u, v] = pq.top();
        pq.pop();
        if (dsu.find(u) != dsu.find(v)) {
            dsu.merge(u, v);
            res -= w;
        }
    }
};