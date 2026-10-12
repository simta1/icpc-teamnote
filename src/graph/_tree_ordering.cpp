vector<int> p(n + 1, -1), order;
order.push_back(root);
for (int index = 0; index < n; ++index) {
	int cur = order[index];
	for (int nxt : graph[cur]) if (nxt != p[cur]) {
		p[nxt] = cur;
		order.push_back(nxt);
	}
}
