// 날짜 일 수 변환
bool isLeapYear(int year) { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }
int dateToDays(int y, int m, int d) { // 1년 1월 1일부터 y년 m월 d일까지 날짜 수 계산(당일 포함)
	static constexpr array<int, 13> pfs = []() {
		array<int, 13> res = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		for (int i = 1; i < res.size(); ++i) res[i] += res[i - 1];
		return res;
	}();

	return (y - 1) * 365 + ((y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400) // y년 1월 1일 전날까지의 일 수
		+ pfs[m - 1] + (isLeapYear(y) && m > 2) // y년 m월 1일 전날까지의 일 수
		+ d;
}

// 날짜 요일 변환
int f(int y, int m, int k) { // 일(0), 월(1), 화(2), 수(3), 목(4), 금(5), 토(6)
	if (m <= 2) {
		--y;
		m += 12; 
	}
	m -= 2;
	int c = y / 100, d = y % 100;
	int w = d + d / 4 - 2 * c + c / 4 + (13 * m - 1) / 5 + k;
	return (w % 7 + 7) % 7;
}