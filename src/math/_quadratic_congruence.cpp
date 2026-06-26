pll quadraticCongruence(ll a, ll b, ll p) { // x^2 + ax + b === 0 (mod p) // 해가 없다면 {-1, -1} 리턴
    assert (a >= 0 && a < p);
    assert (b >= 0 && b < p);
    if (p == 2) {
        if (a && b) return {-1, -1};
        if (a && !b) return {0, 1};
        if (!a && b) return {1, 1};
        return {0, 0};
    }
    else {
        ll c = (a + (a & 1) * p) >> 1;
        ll d = (multiply(c, c, p) - b + p) % p;
        ll sqr = tonelliShanks(d, p);
        if (!~sqr) return {-1, -1};
        return {(p - c + p - sqr) % p, (p - c + sqr) % p};
    }
}
// (x+a/2)^2 === -b + (a/2)^2 (mod p)
// c := a/2 (mod p)
// d := c^2 - b (mod p)
