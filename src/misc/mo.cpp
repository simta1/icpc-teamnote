#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
vector<T> mo(const vector<int> &v, const vector<pair<int, int> > &_queries, const bool is1based = true) { // O((N+Q)sqrt(N)T(N)) // T(N)은 push(), pop()의 시간복잡도   
	int q = _queries.size();
	assert(q);

	struct Query { int s, e, idx; };
	vector<Query> queries(q);
	vector<T> answer(q);

	for (int i = 0; i < q; i++) {
		queries[i].s = _queries[i].first - is1based;
		queries[i].e = _queries[i].second - is1based;
		queries[i].idx = i;
	}

	int sqr = sqrt(v.size());
	sort(queries.begin(), queries.end(), [&sqr](const Query& a, const Query& b) {
		if (a.s / sqr != b.s / sqr) return a.s < b.s;
		return (a.s / sqr) & 1 ? a.e < b.e : a.e > b.e;
	});

	// --- 채우고 사용
	auto push_back = [&](int idx) {};
	auto pop_back = [&](int idx) {};
	auto push_front = push_back;
	auto pop_front = pop_back;
	auto query = [&]() {};
	// ---

	int s = queries[0].s, e = queries[0].e;
	for (int i = s; i <= e; i++) push_back(i);
	answer[queries[0].idx] = query();

	for (int i = 1; i < queries.size(); i++) {
		int idx1 = queries[i].s, idx2 = queries[i].e;
		while (s > idx1) push_front(--s);
		while (e < idx2) push_back(++e);
		while (s < idx1) pop_front(s++);
		while (e > idx2) pop_back(e--);
		answer[queries[i].idx] = query();
	}

	return answer;
}
