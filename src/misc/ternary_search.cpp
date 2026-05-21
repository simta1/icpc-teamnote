auto ternarySearch = [&](ll l, ll r) { // min
    ll lo = l, hi = r;
    while (hi - lo >= 3) {
        ll p = (lo * 2 + hi) / 3, q = (lo + hi * 2) / 3;
        if (f(p) > f(q)) lo = p; // max이면 if (f(p) < f(q))
        else hi = q;
    }
    auto res = f(lo);
    for (ll i = lo + 1; i <= hi; i++) res = min(res, f(i));
    return res;
};