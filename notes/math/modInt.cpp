using ll = long long;
template <ll MOD>
struct mint {
    static_assert(MOD > 1);
    static_assert(MOD - 1 <= numeric_limits<long long>::max() / 2, "operator+ 수정해야 함");
    ll value = 0;
    explicit mint() : value(0) {}
    explicit mint(ll n) {
        value = n % MOD;
        if (value < 0) value += MOD;
    }
    tuple<ll, ll, ll> egcd(ll a, ll b) const { // ax + by = gcd(a, b)
        if (b == 0) return {1, 0, a};
        auto [x, y, g] = egcd(b, a % b);
        return {y, x - (a / b) * y, g};
    }
    mint inv() const {
        auto [x, y, g] = egcd(value, MOD);
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