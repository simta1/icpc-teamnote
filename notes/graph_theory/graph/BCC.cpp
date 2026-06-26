vector<vector<pair<int, int> > > getBCC(int n, const vector<vector<int> > &adj) { // O(V + E)
    vector<int> dfsn(n + 1, 0);
    stack<pair<int, int> > edgeStack;
    vector<vector<pair<int, int> > > bccs;
    int dfsi = 0;
    function<int(int, int)> dfs = [&](int cur, int parent) -> int {
        int low = dfsn[cur] = ++dfsi;
        for (auto next : adj[cur]) if (next != parent) {
            if (dfsn[next] < dfsn[cur]) edgeStack.emplace(cur, next);
            if (!dfsn[next]) {
                int nextLow = dfs(next, cur);
                low = min(low, nextLow);
                if (nextLow >= dfsn[cur]) {
                    vector<pair<int, int> > bcc;
                    while (!edgeStack.empty()) {
                        auto [u, v] = edgeStack.top();
                        edgeStack.pop();
                        bcc.emplace_back(u, v);
                        if ((u == cur && v == next) || (u == next && v == cur)) break;
                    }
                    bccs.push_back(bcc);
                }
            }
            else low = min(low, dfsn[next]);
        }
        return low;
    };
    for (int i = 1; i <= n; i++) if (!dfsn[i]) dfs(i, -1);
    return bccs;
}
vector<int> getNodeOfBCC(int n, const vector<pair<int, int> > &bcc) {
    static int trueValue = 1;
    static vector<int> visited(n + 1);
    if (visited.size() < n + 1) visited.resize(n + 1); // 테스트케이스 여러 개인 문제면 n 바뀔 수 있음
    vector<int> res;
    for (auto [u, v] : bcc) {
        if (visited[u] != trueValue) res.push_back(u);
        if (visited[v] != trueValue) res.push_back(v);
        visited[u] = visited[v] = trueValue;
    }
    ++trueValue;
    return res;
/*  int E = bcc.size(), V = getNodeOfBCC(n, bcc).size();라 할 때
    E >= V라면 사이클을 이루는 BCC (E = V라면 단순사이클, E>V라면 해당 BCC의 모든 정점을 지나는 사이클에 chord가 존재)
    E < V라면 (E=0, V=1) 혹은 단절선(E=1, V=2) 뿐임     */
}
// 2개 이상의 BCC에 포함되는 정점은 단절점이다.(역도 성립)   
// $V=2$, $E=1$라면 해당 BCC는 단절선이다.(역도 성립)   

// ex) BCC 사용해서 단절점, 단절선 개수 세기
int cutVertexes = 0, bridges = 0;
auto bccs = getBCC(n, adj);
vector<int> cnt(n + 1);
for (auto &bcc : bccs) {
    auto nodes = getNodeOfBCC(n, bcc);
    int V = nodes.size();
    int E = bcc.size();
    for (auto e : nodes) criticalNodes += (++cnt[e] == 2);
    bridges += (V == 2 && E == 1);
}
cout << cutVertexes << "\n"; // 단절점 개수 
cout << bridges << "\n"; // 단절선 개수 