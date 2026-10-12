struct Node {
	ll sum, l, r, lr;
	Node(ll x) : sum(x), l(x), r(x), lr(x) {}
	Node(ll sum, ll l, ll r, ll lr) : sum(sum), l(l), r(r), lr(lr) {}
};
Node op(const Node &a, const Node &b) {
	return {
		a.sum + b.sum,
		max(a.l, a.sum + b.l),
		max(b.r, a.r + b.sum),
		max({a.lr, b.lr, a.r + b.l})
	};
}
Node e() {
	return {0, -INF, -INF, -INF};
}
// 비어있지 않은 연속 부분 구간 중 최대합 계산
// 값이 전부 음수면 답이 0이 대신 음수들 중 최대값 나옴
// v[1:n]이 A과 B로 이루어졌을 때 A로만 이루어진 구간의 최대 길이:
// A -> 1, B -> -n으로 두면 최대 연속 부분합과 같음
