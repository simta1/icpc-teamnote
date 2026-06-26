vector<int> getArticulationPoints(int n, const vector<vector<int> > &adj) { // O(V + E)
    vector<int> dfsn(n + 1);
    vector<bool> isCutVertex(n + 1);
    int dfsi = 0;
    function<int(int, int)> dfs = [&](int cur, int parent) -> int {
        int low = dfsn[cur] = ++dfsi;
        int child = 0;
        for (auto next : adj[cur]) if (next != parent) {
            if (!dfsn[next]) {
                ++child;
                int nextLow = dfs(next, cur);
                low = min(low, nextLow);
                isCutVertex[cur] = isCutVertex[cur] | (~parent && nextLow >= dfsn[cur]);
            }
            else low = min(low, dfsn[next]);
        }
        isCutVertex[cur] = isCutVertex[cur] | (!~parent && child > 1);
        return low;
    };
    for (int i = 1; i <= n; i++) if(!dfsn[i]) dfs(i, -1);
    vector<int> res;
    for (int i = 1; i <= n; i++) if (isCutVertex[i]) res.push_back(i);
    return res;
}
// 단절점의 조건은 `nextLow >= in[cur]` 단절선의 조건 `nextLow > in[cur]`과 다름에 주의   
// 단절선이기 위해선 간선 이전의 모든 정점에 갈 수 없어야 하므로 이전 정점인 cur도 갈 수 없어야 하고,   
// 단절점의 경우 cur에 갈 수 있다고 해도 어차피 정점이 제거되므로 상관없음   