vector<int> sz(n + 1);
vector<bool> rm(n + 1);
auto get_sz = [&](auto &&get_sz, int cur, int par) -> int {
    sz[cur] = 1;
    for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
        sz[cur] += get_sz(get_sz, nxt, cur);
    }
    return sz[cur];
};
auto get_ct = [&](auto &&get_ct, int cur, int par, int tot) -> int {
    for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
        if (sz[nxt] * 2 > tot) return get_ct(get_ct, nxt, cur, tot);
    }
    return cur;
};

vector<int> cpar(n + 1, -1), cdep(n + 1);
auto build = [&](auto &&build, int cur, int par) -> void {
    int tot = get_sz(get_sz, cur, -1);
    int ct = get_ct(get_ct, cur, -1, tot);
    if (~par) {
        cpar[ct] = par;
        cdep[ct] = cdep[par] + 1;
    }
    rm[ct] = 1;
    for (auto nxt : adj[ct]) if (!rm[nxt]) {
        build(build, nxt, ct);
    }
};
build(build, 1, -1);
