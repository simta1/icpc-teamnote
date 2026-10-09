constexpr int MX = 100; // 분모 MX이하인 기약분수만 고려
auto dfs = [&](auto &&dfs, int a, int b, int c, int d) -> void { // O(MX^2)
    int x = a + c, y = b + d;
    if (y <= MX) {
        dfs(dfs, a, b, x, y);
        cout << x << " " << y << "\n";
        dfs(dfs, x, y, c, d);
    }
};
dfs(dfs, 0, 1, 1, 1); // 0과 1사이 모든 기약분수
dfs(dfs, a, b, c, d); // a/b 초과 c/d 미만 모든 기약분수 // bc - ad = 1이어야 됨
