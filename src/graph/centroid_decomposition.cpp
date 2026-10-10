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

ll ans = 0;
vector<int> a(n + 1);
vector<int> dirty;
auto f = [&](auto &&f, int cur, int par) -> void {
    // ans <- cur 기여분만큼 업데이트하기
    for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) f(f, nxt, cur);
};
auto update = [&](auto &&update, int cur, int par) -> void {
    // a[cur];
    // dirty.push_back(cur);
    for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) update(update, nxt, cur);
};
auto dnc = [&](auto &&dnc, int cur) -> void {
    int tot = get_sz(get_sz, cur, -1);
    int ct = get_ct(get_ct, cur, -1, tot);
    rm[ct] = 1;
    for (auto nxt : adj[ct]) if (!rm[nxt]) {
        f(f, nxt, -1);
        update(update, nxt, -1);
    }
    // centroid가 끝점인 경로도 세야됨
    for (auto x : dirty) a[x] = 0;
    dirty.clear();
    for (auto nxt : adj[ct]) if (!rm[nxt]) dnc(dnc, nxt);
};
