struct Graph {
    struct Edge { int to, rev, c, oc; };
    vector<vector<Edge> > adj;
    vector<int> visited;
    int trueValue = 0;
    Graph(int n) : adj(n), visited(n) {} // 0-based
    void addEdge(int u, int v, int c) {
        adj[u].push_back({v, adj[v].size(), c, c});
        adj[v].push_back({u, adj[u].size() - 1, 0, 0});
    }
    int dfs(int cur, int t, int f) {
        if (cur == t) return f;
        visited[cur] = trueValue;
        for (auto &e : adj[cur]) if (visited[e.to] != trueValue && e.c > 0) {
            int pushed = dfs(e.to, t, min(f, e.c));
            if (pushed) {
                e.c -= pushed;
                adj[e.to][e.rev].c += pushed;
                return pushed;
            }
        }
        return 0;
    }
    int maxFlow(int s, int t) { // ford fulkerson // O(Ef)
        int res = 0;
        while (1) {
            ++trueValue;
            int pushed = dfs(s, t, numeric_limits<int>::max());
            if (!pushed) break;
            res += pushed;
        }
        return res;
    }
};
