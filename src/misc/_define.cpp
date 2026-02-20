#ifdef LOCAL
    #define DEBUG(x) { cerr << #x << " = " << x << endl; }
    #define DEBUG_ITER(x) { \
        cerr << #x << " = [ "; \
        for (auto _ : x) cerr << _ << ' '; \
        cerr << "]" << endl; \
    }
#else
    #define DEBUG(x) {}
    #define DEBUG_ITER(x) {}
#endif

#define prt(x) #x << ": " << x
#define SPC << " " <<