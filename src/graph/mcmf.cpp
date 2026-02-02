template <typename C, typename F>
struct Graph {
    struct Edge {
        int to, rev;
        C cost;
        F c, oc;
    };
    vector<vector<Edge> > adj;
    C DIST_INF = numeric_limits<C>::max();
    Graph(int n) : adj(n) {} // 0-based
    void addEdge(int a, int b, C cost, F c, F rcap = 0) { // 양방향이면 rcap=c로 호출
        adj[a].push_back({b, adj[b].size(), cost, c, c});
        adj[b].push_back({a, adj[a].size() - 1, -cost, rcap, rcap});
    }
    pair<C, F> mcmf(int s, int t, F targetFlow = numeric_limits<F>::max()) { // O(VEf) // average O(Ef)
        C minCost = 0;
        F maxFlow = 0;
        vector<Edge *> pedge(adj.size());
        vector<C> dist(adj.size());
        vector<bool> inq(adj.size());
        while (maxFlow < targetFlow) {
            fill(dist.begin(), dist.end(), DIST_INF);
            dist[s] = 0;
            queue<int> q;
            q.push(s);
            inq[s] = true;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                inq[cur] = false;
                for (int i = 0; i < adj[cur].size(); i++) {
                    auto &e = adj[cur][i];
                    if (e.c && dist[e.to] > dist[cur] + e.cost) {
                        dist[e.to] = dist[cur] + e.cost;
                        pedge[e.to] = &e;
                        if (!inq[e.to]) {
                            q.push(e.to);
                            inq[e.to] = true;
                        }
                    }
                }
            }
            if (dist[t] == DIST_INF) break;
            F f = targetFlow - maxFlow;
            for (int cur = t; cur != s;) {
                auto &e = *pedge[cur];
                f = min(f, e.c);
                cur = adj[e.to][e.rev].to;
            }
            for (int cur = t; cur != s;) {
                auto &e = *pedge[cur];
                e.c -= f;
                adj[e.to][e.rev].c += f;
                cur = adj[e.to][e.rev].to;
            }
            minCost += f * dist[t];
            maxFlow += f;
        }
        return {minCost, maxFlow};
    }
};