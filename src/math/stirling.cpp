// P(n, k): n을 순서 없이 k개의 양의 정수의 합으로 분할
static ll part[N + 1][N + 1] = {{1}};
// 제1종 스털링 : n개의 원소를 k개의 사이클로 분할
static ll st1[N + 1][N + 1] = {{1}};
// 제2종 스털링 수: n개의 원소를 k개의 집합으로 분할
static ll st2[N + 1][N + 1] = {{1}};
for (int n = 1; n <= N; n++) {
    for (int k = 1; k <= n; k++) {
        part[n][k] = (part[n-1][k-1] + part[n-k][k]) % MOD;
        st1[n][k] = (st1[n-1][k-1] + (n-1)*st1[n-1][k]) % MOD;
        st2[n][k] = (st2[n-1][k-1] + k*st2[n-1][k]) % MOD;
    }
}
