template <typename F>
int rightMost(int l, F f) const { // f([l:r])=true인 최대 r // 만족하는 r 없다면 l-1리턴
	int node = l | sz;
	T acc = e();
	node >>= __builtin_ctz(node);
	while (f(op(acc, tree[node]))) {
		acc = op(acc, tree[node++]);
		if (node & (node - 1)) node >>= __builtin_ctz(node);
		else return n - 1;
	}
	while (node < sz) {
		node <<= 1;
		if (f(op(acc, tree[node]))) acc = op(acc, tree[node++]);
	}
	return (node ^ sz) - 1;
}
template <typename F>
int leftMost(int r, F f) const { // f([l:r])=true인 최소 l // 만족하는 l 없다면 r+1리턴
	int node = r | sz;
	T acc = e();
	node = max(1, node >> __builtin_ctz(~node));
	while (f(op(tree[node], acc))) {
		acc = op(tree[node--], acc);
		if ((node + 1) & node) node = max(1, node >> __builtin_ctz(~node));
		else return 0;
	}
	while (node < sz) {
		node = node << 1 | 1;
		if (f(op(tree[node], acc))) acc = op(tree[node--], acc);
	}
	return (node ^ sz) + 1;
}
int kthSmallest(int l, T k) const { // qry([l, r]) >= k인 최소 r
	if (qry(l, n - 1) < k) return -1;
	return rightMost(l, [&](T sum) { return sum < k; }) + 1;
}
int kthLargest(int r, T k) const { // qry([l, r]) >= k인 최대 l
	if (qry(0, r) < k) return -1;
	return leftMost(r, [&](T sum) { return sum < k; }) - 1;
}