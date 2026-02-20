vector<int> dequeTrickMin(int len, const vector<int> &v) { // res[i]는 v[max(0, i - len + 1)]~v[i]의 최솟값 // 즉, 정확히 길이가 len인 구간의 최솟값은 res[len-1:n)에 저장됨
    vector<int> res(v.size());
    deque<int> dq;
    for (int i = 0; i < v.size(); i++) {
        while (!dq.empty() && v[dq.back()] > v[i]) dq.pop_back(); // min
        // while (!dq.empty() && v[dq.back()] < v[i]) dq.pop_back(); // max
        dq.push_back(i);
        if (i - dq.front() + 1 > len) dq.pop_front();
        res[i] = v[dq.front()];
    }
    return res;
}
// cmp 복잡할때
deque<int> dq;
auto cmp = [&](int front, int back) { // front에 구하려는 값이 들어가야 함
    // ex) min이면 return v[front] <= v[back];
};
for (int i = 0; i < v.size(); i++) {
    while (!dq.empty() && !cmp(dq.back(), i)) dq.pop_back();
    dq.push_back(i);
    if (i - dq.front() + 1 > len) dq.pop_front();
}