int get_sz(int cur, int par) {
    sz[cur] = 1;
    for (auto next : adj[cur]) if (next != par) sz[cur] += get_sz(next, cur);
    return sz[cur];
}
int get_ct(int cur, int par) { // O(N)
    for (auto next : adj[cur]) if (next != par && sz[next] * 2 > n) return get_ct(next, cur);
    return cur;
}
