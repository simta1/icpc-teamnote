struct Compare {
    bool operator()(const Edge &bottom, const Edge &top) const {
        return bottom.cost > top.cost; // min pq
    }
};
priority_queue<T, vector<T>, Compare> pq;

// 전역함수
bool cmp(int x, int y) {}
set<int,decltype(&cmp)> s(cmp);
priority_queue<int,vector<int>,decltype(&cmp)> pq(cmp);

// 람다
priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
set<int, decltype(cmp)> s(cmp);