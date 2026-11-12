static ll dp[len + 1][2]; // dp[i][tight]
dp[0][1] = 1;
for (int i = 0; i < len; i++) {
	for (int tight = 0; tight < 2; tight++) {
		for (int d = 0; d <= (tight ? digits[i] : 9); d++) {
			dp[i + 1][tight && d == digits[i]] += dp[i][tight];
		}
	}
}

static ll dp[len + 1][2][2]; // dp[i][tight][started]
dp[0][1][0] = 1; // tight=true, started=false
for (int i = 0; i < len; i++) {
	for (int tight = 0; tight < 2; tight++) {
		for (int started = 0; started < 2; started++) {
			for (int d = 0; d <= (tight ? digits[i] : 9); d++) {
				// dp전파가 started 여부와 관련없는 경우
				dp[i + 1][tight && d == digits[i]][started || d] += dp[i][tight][started];

				// dp의 다른 차원들이 started 여부에 따라 조건분기가 필요한 경우
				if (started || d) {
					dp[i + 1][tight && d == digits[i]][true] += dp[i][tight][started];
				}
				else {
					dp[i + 1][tight && d == digits[i]][false] += dp[i][tight][started];
				}
			}
		}
	}
}

// 작은 자리수부터 전이
reverse(digits.begin(), digits.end());
static ll dp[len + 1][3]; // dp[i][tight]
dp[0][1] = 1;
for (int i = 0; i < len; i++) {
	for (int cmp = 0; cmp < 3; cmp++) {
		for (int d = 0; d < 10; d++) {
			int ncmp;
			if (d < digits[i]) ncmp = 0;
			else if (d == digits[i]) ncmp = cmp;
			else ncmp = 2;
			dp[i + 1][ncmp] += dp[i][cmp];
		}
	}
}
