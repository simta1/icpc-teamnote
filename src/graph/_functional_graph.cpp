vector<int> state(n + 1);
vector<int> path;
auto dfs = [&](auto &&dfs, int cur) -> void {
    state[cur] = 1;
    path.push_back(cur);
    for (auto nxt : adj[cur]) {
        if (!state[nxt]) dfs(dfs, nxt);
        else if (state[nxt] == 1) {
            vector<int> cycle;
            for (int i = path.size() - 1; i >= 0; i--) {
                cycle.push_back(path[i]);
                if (path[i] == nxt) break;
            }
            reverse(cycle.begin(), cycle.end());
            //
        }
    }
    path.pop_back();
    state[cur] = 2;
};
for (int i = 1; i <= n; i++) if (!state[i]) dfs(dfs, i);
