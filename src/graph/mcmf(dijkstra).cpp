#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
template <typename C, typename F>
struct Graph {
    struct edge {
        int to, rev;
        F c, oc;
        C cost;
        int from;
    };
    int n;
    vector<vector<edge> > adj;
    vector<int> seen;
    vector<C> dist, pi;
    vector<edge*> pedge;
    const C DIST_INF = numeric_limits<C>::max() / 4;
    Graph(int n) : n(n), adj(n), seen(n), dist(n), pi(n), pedge(n) {} // 0-based
    void addEdge(int a, int b, C cost, F c) {
        adj[a].push_back({b, adj[b].size(), c, c, cost, a});
        adj[b].push_back({a, adj[a].size() - 1, 0, 0, -cost, b});
    }
    void path(int s) {
        fill(seen.begin(), seen.end(), 0);
        fill(dist.begin(), dist.end(), DIST_INF);
        dist[s] = 0;
        using elem = pair<C, int>;
        using pq_t = __gnu_pbds::priority_queue<elem, greater<elem> >;
        pq_t q;
        vector<typename pq_t::point_iterator> its(n);
        q.push({0, s});
        while (!q.empty()) {
            int cur = q.top().second;
            q.pop();
            seen[cur] = 1;
            C di = dist[cur] + pi[cur];
            for (auto &e : adj[cur]) if (e.c && !seen[e.to]) {
                C val = di - pi[e.to] + e.cost;
                if (dist[e.to] > val) {
                    dist[e.to] = val;
                    pedge[e.to] = &e;
                    if (its[e.to] == q.end()) its[e.to] = q.push({dist[e.to], e.to});
                    else q.modify(its[e.to], {dist[e.to], e.to});
                }
            }
        }
        for (int i = 0; i < n; i++) pi[i] = min(pi[i] + dist[i], DIST_INF);
    }
    pair<C, F> mcmf(int s, int t) {
        C minCost = 0;
        F maxFlow = 0;
        while (path(s), seen[t]) {
            F f = numeric_limits<F>::max();
            for (edge *e = pedge[t]; e; e = pedge[e->from]) f = min(f, e->c);
            for (edge *e = pedge[t]; e; e = pedge[e->from]) {
                e->c -= f;
                adj[e->to][e->rev].c += f;
            }
            maxFlow += f;
            minCost += f * (pi[t] - pi[s]);
        }
        return {minCost, maxFlow};
    }
    void setpi(int s) { // 음수비용 존재 시 mcmf전에 호출필요 // O(VE)
        fill(pi.begin(), pi.end(), DIST_INF);
        pi[s] = 0;
        int it = n, ch = 1; ll v;
        while (ch-- && it--)
            for (int i = 0; i < n; i++) if (pi[i] != DIST_INF)
                for (edge& e : adj[i]) if (e.c)
                    if ((v = pi[i] + e.cost) < pi[e.to])
                        pi[e.to] = v, ch = 1;
        assert(it >= 0); // 비용 음수사이클 존재
    }
};