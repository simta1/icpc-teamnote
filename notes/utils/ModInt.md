[카테고리](/README.md)
## ModInt
```cpp
using ll = long long;
template <ll MOD>
class mint {
    static_assert(MOD > 1);
    static_assert(MOD - 1 <= numeric_limits<long long>::max() / 2, "operator+ 수정해야 함");

public:
    ll value;

    explicit mint() = default;
    explicit mint(ll n) {
        value = n % MOD;
        if (value < 0) value += MOD;
    }

    tuple<ll, ll, ll> extendedGCD(ll a, ll b) const { // ax + by = gcd(a, b)
        if (b == 0) return {1, 0, a};
        auto [x, y, g] = extendedGCD(b, a % b);
        return {y, x - (a / b) * y, g};
    }

    mint inv() const {
        auto [x, y, g] = extendedGCD(value, MOD);
        assert(g == 1); // g!=1이면 역원 존재 안함
        return mint(x);
    }

    mint pow(ll n) const {
        mint base = *this, res(1);
        while (n) {
            if (n & 1) res *= base;
            base *= base;
            n >>= 1;
        }
        return res;
    }
    
    mint operator-() const { return mint(-value); }
    mint& operator+=(const mint &other) { if ((value += other.value) >= MOD) value -= MOD; return *this; }
    mint& operator-=(const mint &other) { if ((value -= other.value) < 0) value += MOD; return *this; }
    mint& operator*=(const mint &other) {
        if constexpr ((MOD - 1) > numeric_limits<ll>::max() / (MOD - 1)) value = ll(__int128(value) * other.value % MOD);
        else value = value * other.value % MOD;
        return *this;
    }
    mint& operator/=(const mint &other) { return *this *= other.inv(); }
    mint operator+(const mint &other) const { return mint(value) += other; }
    mint operator-(const mint &other) const { return mint(value) -= other; }
    mint operator*(const mint &other) const { return mint(value) *= other; }
    mint operator/(const mint &other) const { return mint(value) /= other; }
    bool operator==(const mint &other) const { return value == other.value; }
    bool operator!=(const mint &other) const { return value != other.value; }
    friend istream &operator>>(istream &is, mint &m) { ll x; is >> x; m = mint(x); return is; }
    friend ostream &operator<<(ostream &os, const mint &m) { return os << m.value; }
};
```

### 사용설명
$\text{MOD} <= 4611686018427387904$인 상황을 가정한 코드임(static_assert로 확인하게 해둠)   
만약 $\text{MOD} > 4611686018427387904$라면 `2 * (MOD - 1) < numeric_limits<ll>::max()`를 만족하지 않으므로 덧셈 과정에서 오버플로우가 발생할 수 있음   
`operator*`에서 한 것처럼 `if constexpr`으로 케이스를 나누어 해결할 수 있지만 코드 길이가 길어지기에 넣지 않았고 $\text{MOD} <= 4611686018427387904$를 강제하기로 함.   
애초에 ps에서 $\text{MOD}$로 주어지는 값의 범위는 보통 1e10을 넘지 않기에 앞으로도 이 코드 그대로 사용할 듯

### 문제
[]()
문제 풀 때 종종 사용할 일이 있기도 하고, [NTT](/수학/NTT.md#ntt-number-theoretic-transform)구현에서 fft 코드 그대로 가져가 사용할 때도 유용함   

### 참고링크
https://memoacmicpc.tistory.com/entry/%EA%B8%B0%EB%B3%B8-%EC%9D%B4%EB%A1%A0   