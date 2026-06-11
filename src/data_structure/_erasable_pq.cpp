template <typename T, bool Maximize = true>
struct ErasablePQ {
    conditional_t<Maximize, priority_queue<T>, priority_queue<T, vector<T>, greater<T> > > q, rm;
    void normalize() {
        while (!q.empty() && !rm.empty() && q.top() == rm.top()) {
            q.pop(), rm.pop();
        }
    }
    void push(const T& t) { q.push(t); }
    T top() {
        normalize();
        return q.top();
    }
    void pop() {
        normalize();
        q.pop();
    }
    void erase(const T& t) { rm.push(t); }
};
