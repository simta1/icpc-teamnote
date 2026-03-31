// 집합을 전부 합치기까지 총 원소 이동 횟수 O(N logN)
a = dsu.find(a);
b = dsu.find(b);
if (v[a].size() > v[b].size()) {
    v[a].insert(v[a].end(), v[b].begin(), v[b].end());
    dsu.merge(b, a); // parent[find(b)] = find(a);
}
else {
    v[b].insert(v[b].end(), v[a].begin(), v[a].end());
    dsu.merge(a, b); // parent[find(a)] = find(b);
}