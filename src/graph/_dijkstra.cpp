auto dijkstra = [&](int s) { // O(E logV)
    vector<dist_t> dist(n + 1, INF);
    dist[s] = 0;
    using elem = pair<dist_t, int>;
    priority_queue<elem, vector<elem>, greater<elem>> pq;
    pq.emplace(dist[s], s);
    while (!pq.empty()) {
        auto [distance, cur] = pq.top();
        pq.pop();
        if (distance > dist[cur]) continue;
        for (auto [nxt, cost] : adj[cur]) if (dist[nxt] > dist[cur] + cost) {
            dist[nxt] = dist[cur] + cost;
            pq.emplace(dist[nxt], nxt);
        }
    }
    return dist;
};