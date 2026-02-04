// 집합을 전부 합치기까지 원소 이동 횟수는 총 O(N logN)
a = dsu.find(a);
b = dsu.find(b);
if (v[a].size() > v[b].size()) {
    for (auto [l, r] : v[b].s) v[a].emplace(l, r);
    dsu.merge(b, a); // parent[find(b)] = find(a);
}
else {
    for (auto [l, r] : v[a].s) v[b].emplace(l, r);
    dsu.merge(a, b); // parent[find(a)] = find(b);
}