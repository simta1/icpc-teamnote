sort(v.begin(), v.end());
assert(is_sorted(qs.begin(), qs.end()));
int lb = 0, ub = 0;
for (auto x : qs) {
	while (lb < v.size() && v[lb] < x) ++lb;
	while (ub < v.size() && v[ub] <= x) ++ub;
	// lb = lower_bound(v.begin(), v.end(), x) - v.begin();
	// ub = upper_bound(v.begin(), v.end(), x) - v.begin();
}
