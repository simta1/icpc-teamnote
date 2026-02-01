template <typename F>
struct Dinic {
    struct Edge {
        int to, rev;
        F c, oc;
        F flow() { return max(oc - c, F(0)); }
    };
    vector<int> lvl, ptr, q;
    vector<vector<Edge> > adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {} // 0-based
    void addEdge(int a, int b, F c, F rcap = 0) { // 양방향이면 rcap=c로 호출
        if (a == b) return; // self-loop는 최대유량에 영향 X
        adj[a].push_back({b, adj[b].size(), c, c});
        adj[b].push_back({a, adj[a].size() - 1, rcap, rcap});
    }
    F dfs(int cur, int t, F mn) {
        if (cur == t || !mn) return mn;
        for (int &i = ptr[cur]; i < adj[cur].size(); i++) {
            auto &e = adj[cur][i];
            if (lvl[e.to] != lvl[cur] + 1) continue;
            if (F f = dfs(e.to, t, min(mn, e.c))) {
                e.c -= f, adj[e.to][e.rev].c += f;
                return f;
            }
        }
        return 0;
    }
    template <bool scaling=false> F maxFlow(int s, int t) { // O(V^2 E) // max(cap)이 큰 경우 scaling=true가 빠름
        F res = 0; q[0] = s;
        for (int i = scaling ? 0 : 30; i < 31; i++) do {
            lvl = ptr = vector<int>(q.size());
            int qs = 0, qe = lvl[s] = 1;
            while (qs < qe && !lvl[t]) {
                int cur = q[qs++];
                for (Edge &e : adj[cur]) if (!lvl[e.to] && e.c >> (30 - i)) {
                    q[qe++] = e.to, lvl[e.to] = lvl[cur] + 1;
                }
            }
            while (F f = dfs(s, t, numeric_limits<F>::max())) res += f;
        } while (lvl[t]);
        return res;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; } // min-cut에서 source 집합에 속하는지
};
// vector<pair<int, int> ref;
// ref.emplace_back(u, graph.adj[u].size()); graph.addEdge(u, v);
// auto [u, idx] = ref[i]; cout << graph.adj[u][idx].flow() << "\n";
// O(min(Ef, V^2 E)), all cap = 1: O(min(V^{2/3}, E^{1/2})E)
// dinic with scaling O(VE log(max_cap))
// 근데 보통 그냥 dinic이 더 빠름, 오히려 max_cap이 클 때 dinic with scaling이 좋음
// 무한간선 많은 경우 proxysource -> source로 K 용량의 간선을 두고 계산하면 애초에 최대유량이 K만큼으로 제한되므로 오버플로우 방지 가능
// 정점분할 시 양방향이라면 addEdge(out(a), in(b), c), addEdge(out(b), int(a), c)
// 정점분할 시 maxFlow(out(s), in(t))