// directed
vector<int> state(n + 1);
bool has_cycle = false;
auto dfs = [&](auto &&dfs, int cur) -> void {
    state[cur] = 1;
    for (auto nxt : adj[cur]) {
        if (state[nxt] == 0) dfs(dfs, nxt);
        else if (state[nxt] == 1) has_cycle = true;
    }
    state[cur] = 2;
};
for (int i = 1; i <= n; i++) if (!state[i]) dfs(dfs, i);
