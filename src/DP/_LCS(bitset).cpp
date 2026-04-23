// https://gist.github.com/cgiosy/a441de545c9e96b1d7b02cc7a00561f9 ----------------------------- {
#define private public
#include <bitset>
#undef private // 여기까진 #include <bits/stdc++.h>앞에 와야됨
#include <bits/stdc++.h>
using namespace std;
#include <x86intrin.h>
template<size_t _Nw> void _M_do_sub(_Base_bitset<_Nw> &A, const _Base_bitset<_Nw> &B) {
	for (int i = 0, c = 0; i < _Nw; i++) c = _subborrow_u64(c, A._M_w[i], B._M_w[i], (unsigned long long*)&A._M_w[i]);
}
template<> void _M_do_sub(_Base_bitset<1> &A, const _Base_bitset<1> &B) { A._M_w -= B._M_w; }
template<size_t _Nb> bitset<_Nb>& operator-=(bitset<_Nb> &A, const bitset<_Nb> &B) { _M_do_sub(A, B); return A; }
template<size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb> &A, const bitset<_Nb> &B) { bitset<_Nb> C(A); return C-=B; }

template<size_t _Nw> void _M_do_add(_Base_bitset<_Nw> &A, const _Base_bitset<_Nw> &B) {
	for (int i = 0, c = 0; i < _Nw; i++) c = _addcarry_u64(c, A._M_w[i], B._M_w[i], (unsigned long long*)&A._M_w[i]);
}
template<> void _M_do_add(_Base_bitset<1> &A, const _Base_bitset<1> &B) { A._M_w += B._M_w; }
template<size_t _Nb> bitset<_Nb>& operator+=(bitset<_Nb> &A, const bitset<_Nb> &B) { _M_do_add(A, B); return A; }
template<size_t _Nb> inline bitset<_Nb> operator+(const bitset<_Nb> &A, const bitset<_Nb> &B) { bitset<_Nb> C(A); return C+=B; }
// --------------------------------------------------------------------------------------------- }

template <size_t sz>
int LCS(const string &_a, const string &_b) { // time O(NM/64), space O(26*min(n, m)/64)
    const string &a = _a.size() > _b.size() ? _a : _b;
    const string &b = _a.size() > _b.size() ? _b : _a;
    bitset<sz> D, x, S[26]; // 대문자만 있는 경우
    for (int i = 0; i < b.size(); i++) S[b[i] - 'A'][i] = 1;
    for (int i = 0; i < a.size(); i++) {
        x = S[a[i] - 'A'] | D;
        D <<= 1;
        D[0] = 1;
        D = x & (x ^ (x - D));
    }
    return D.count();
}

// 테스트케이스 여러개로 나뉘어 들어올 때
string LCS(const string& a, const string& b) {
    int sz = min(a.size(), b.size());
	if (sz <= 64) return LCS<64>(a, b);
	if (sz <= 128) return LCS<128>(a, b);
	if (sz <= 512) return LCS<512>(a, b);
	if (sz <= 1024) return LCS<1024>(a, b);
	if (sz <= 1024 * 2) return LCS<1024 * 2>(a, b);
    // ...
	return LCS<50000>(a, b);
}

// hirschberg용 코드
template <size_t sz>
vector<int> getDP(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    bitset<sz> D, x, S[26]; // 대문자만 있는 경우
    for (int i = 0; i < m; i++) S[b[i] - 'A'][i] = 1;
    for (int i = 0; i < n; i++) {
        x = S[a[i] - 'A'] | D;
        D <<= 1;
        D[0] = 1;
        D = x & (x ^ (x - D));
    }
    vector<int> dp(m + 1);
    int cur = 0;
    for (int i = 1; i <= m; i++) {
        cur += D[i - 1];
        dp[i] = cur;
    }
    return dp;
}