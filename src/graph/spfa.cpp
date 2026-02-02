auto spfa = [&](int s) { // O(VE) // average O(V+E)
    vector<dist_t> dist(n + 1, INF);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    vector<int> cnt(n + 1);
    ++cnt[s];
    vector<bool> inq(n + 1);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        inq[cur] = false;
        for (auto [next, cost] : adj[cur]) if (dist[next] > dist[cur] + cost) {
            dist[next] = dist[cur] + cost;
            if (inq[next]) continue;
            if (++cnt[next] >= n) return pair{true, dist}; // hasNegCycle
            q.push(next);
            inq[next] = true;
        }
    }
    return pair{false, dist}; // {hasNegCycle, dist}
};