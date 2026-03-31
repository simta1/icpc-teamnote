vector<int> d(n + 1, 1);
for (int i = 3; i <= n; i++) d[i] = (i - 1) * (d[i - 2] + d[i - 1])
// D_n = (n - 1) * (D_{n-2} + D_{n-1})