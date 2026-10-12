vector<T> basis;
auto insert = [&](T x) {
	for (auto e : basis) x = min(x, x ^ e);
	if (x) basis.push_back(x);
};
T mxSum = 0;
auto b = basis; // insert를 계속해야하는 경우 basis의 순서는 바뀌면 안됨
sort(b.rbegin(), b.rend());
for (auto e : b) mxSum = max(mxSum, mxSum ^ e);