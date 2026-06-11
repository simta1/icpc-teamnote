constexpr int N = 1'000'000;
static bool notp[N + 1] = {1, 1};
for (int i = 2; i <= N / i; i++) if (!notp[i]) {
    for (int j = i * i ; j <= N; j += i) notp[j] = 1;
}
vector<int> primes;
for (int i = 2; i <= N; i++) if (!notp[i]) primes.push_back(i);
