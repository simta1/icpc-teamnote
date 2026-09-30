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

vector<int> a(n + 1);
vector<int> dirty;
auto f = [&](auto &&f, int cur, int par) -> ll {
    ll res = 0;
    // res <- cur
    for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
        res += f(f, nxt, cur);
    }
    return res;
};
auto update = [&](auto &&update, int cur, int par) -> void {
    // a[cur];
    // dirty.push_back(cur);
    for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
        update(update, nxt, cur);
    }
};
auto dnc = [&](auto &&dnc, int cur) -> ll {
    int tot = get_sz(get_sz, cur, -1);
    int ct = get_ct(get_ct, cur, -1, tot);
    rm[ct] = 1;
    ll res = 0;
    // centroid가 끝점인 경로도 세야됨
    for (auto nxt : adj[ct]) if (!rm[nxt]) {
        res += f(f, nxt, -1);
        update(update, nxt, -1);
    }
    for (auto x : dirty) a[x] = 0;
    dirty.clear();
    for (auto nxt : adj[ct]) if (!rm[nxt]) {
        res += dnc(dnc, nxt);
    }
    return res;
};
