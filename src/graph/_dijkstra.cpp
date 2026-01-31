// O((V+E)logV)
// 모든 간선의 가중치가 0 이상일 때 사용 가능   
auto dijkstra = [&](int s) {
    vector<dist_t> dist(n + 1, INF);
    dist[s] = 0;
    using elem = pair<dist_t, int>;
    priority_queue<elem, vector<elem>, greater<elem> > pq;
    pq.emplace(dist[s], s);
    while (!pq.empty()) {
        auto [distance, cur] = pq.top();
        pq.pop();
        if (distance > dist[cur]) continue;
        for (auto [next, cost] : adj[cur]) if (dist[next] > dist[cur] + cost) {
            dist[next] = dist[cur] + cost;
            pq.emplace(dist[next], next);
        }
    }
    return dist;
};