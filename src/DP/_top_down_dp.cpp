vector dp(dim1, vector<int>(dim2, -1));

function<int(int, int)> f = [&](int cur, int state) -> int {
    // if (base condition) return ~~;

    int &res = dp[cur][state];
    if (~res) return res;

    res = 0; // visit check
    res = (res + f(next, nextState)) % mod;
    return res;
};

// 1. dp배열 초기화
// -1로 초기화했는지.
// 혹시나 dp값으로 음수값이 가능한 경우에는 불가능한 다른 값으로 초기화했는지.

// 2. 방문 체크
// cur이 계속 증가하거나 감소해서 다시 현재 노드를 방문할 일 없이 단방향으로 전파된다면 필요없지만,
// 혹시나 다시 dfs(cur)이 호출될 가능성이 있다면 무조건 res = (-1이 아닌값)으로 방문체크를 해두어야 무한루프가 방지됨

// 틀린 코드, 무한루프 가능성 있음
res = dfs(cur + 1);
res += dfs(cur - 1);

// good
res = 0;
res += dfs(cur + 1);
res += dfs(cur - 1);

// 3. 방문 체크용 값
// 상황에 따라서 res = -INF;나 res = INF;로 알맞게 방문체크   
// max구해야 될 때 답이 음수가 가능하다면 0이 아니라 -INF로 체크해야 됨.
// f(next)의 계산 과정에서 f(cur)를 다시 호출할 수 있는 경우라면 INF를 `numeric_limits<T>::max()`정도의 큰 수로 두는 건 위험함
// 아래 코드에선 f(cur)내에서 f(cur-1)을 호출하고, f(cur-1)에서 f(cur-1+1)로 다시 f(cur)의 값을 확인하게 되므로
// 이 경우 f(cur)의 값으로 INF가 리턴되어 f(cur-1+1) + 1의 계산에 INF + 1이 들어감.
// 항상 오버플로우 생각하며 INF설정하기.
res = 2e9;
res = min(res, f(cur - 1) + 1);
res = min(res, f(cur + 1) + 1);

// 4. return 했는지
// 혹시 결과 출력 안 되면 return res; 까먹었는지 확인   