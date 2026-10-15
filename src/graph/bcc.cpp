auto get_BCC(int n, int m, const vector<vector<pair<int, int>>> &adj) { // O(V + E)
    vector<vector<int>> bccs;
    vector<int> dfsn(n + 1, 0), s(m);
    int dfsi = 0, top = 0;
    auto dfs = [&](auto &&dfs, int cur, int pid) -> int {
        int low = dfsn[cur] = ++dfsi;
        for (auto [nxt, id] : adj[cur]) if (id != pid) {
            if (!dfsn[nxt]) {
                s[top++] = id;
                int nlow = dfs(dfs, nxt, id);
                low = min(low, nlow);
                if (nlow >= dfsn[cur]) {
                    vector<int> bcc;
                    do { bcc.push_back(s[--top]); } while (s[top] != id);
                    bccs.push_back(bcc);
                }
            }
            else {
                if (dfsn[nxt] < dfsn[cur]) s[top++] = id;
                low = min(low, dfsn[nxt]);
            }
        }
        return low;
    };
    for (int i = 1; i <= n; i++) if (!dfsn[i]) dfs(dfs, i, -1);
    return bccs;
}
vector<int> getNodeOfBCC(int n, const vector<int> &bcc, const vector<pair<int, int>> &edges) {
    static int t = 1;
    static vector<int> visited(n + 1);
    if (visited.size() < n + 1) visited.resize(n + 1); // 테스트케이스 여러 개인 문제면 n 바뀔 수 있음
    vector<int> res;
    for (auto id : bcc) {
        auto [u, v] = edges[id];
        if (visited[u] != t) res.push_back(u);
        if (visited[v] != t) res.push_back(v);
        visited[u] = visited[v] = t;
    }
    ++t;
    return res;
    // int E = bcc.size(), V = getNodeOfBCC(n, bcc).size();
    // E = V : 모든 정점의 차수가 2인 사이클(simple graph면 단순사이클)
    // E > V : 독립적인 사이클 2개 이상 존재
    // E < V : 단절선(E=1, V=2) 뿐임
    // E=0, V=1 : 정점하나만 동떨어진 경우
}
// 2개 이상의 BCC에 포함되는 정점은 단절점이다.(역도 성립)
// $V=2$, $E=1$라면 해당 BCC는 단절선이다.(역도 성립)
