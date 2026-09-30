auto bfs = [&](int s) {
    vector<int> dist(n + 1, -1), p(n + 1, -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto nxt : adj[cur]) if (!~dist[nxt]) {
            dist[nxt] = dist[cur] + 1;
            p[nxt] = cur;
            q.push(nxt);
        }
    }
    return pair{dist, p};
};

auto d1 = bfs(1).first;
int a = max_element(d1.begin(), d1.end()) - d1.begin();
auto [dist, p] = bfs(a);
int b = max_element(dist.begin(), dist.end()) - dist.begin();
int D = dist[b];
