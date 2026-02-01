template<typename T, T (*op)(const T&, const T&), T (*e)()>
class SegmentTree {
private:
    int n, sz, log;
    vector<T> tree;

    static int pow2GE(int n) { assert(n); return 1 << 32 - __builtin_clz(n) - !(n & ~-n); }

public:
    SegmentTree() = default;
    SegmentTree(int n) : SegmentTree(vector<T>(n, e())) {}
    SegmentTree(const vector<T>& v) : n(v.size()) { // vector v는 0-based로 넘겨주지만 이후 update, query 등은 1-based로 하게 됨에 주의
        sz = pow2GE(n);
        tree = vector<T>(sz << 1, e());
        for (int i = 0; i < n; i++) tree[sz + i] = v[i];
        for (int i = sz - 1; i >= 1; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
    }

    void updateChange(int i, T val) { // 1-based
        assert(1 <= i && i <= n);
        tree[--i |= sz] = val;
        while (i >>= 1) tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
    }

    void updateAdd(int i, T val) { // 1-based
        assert(1 <= i && i <= n);
        --i |= sz;
        tree[i] = op(tree[i], val);
        while (i >>= 1) tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
    }
    
    T get(int i) const { // 1-based
        assert(1 <= i && i <= n);
        return tree[--i | sz];
    }

    T query(int l, int r) const { // 1-based // [l:r]
        assert(1 <= l && l <= r && r <= n);
        T resL = e(), resR = e();
        for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) resL = op(resL, tree[l++]);
            if (~r & 1) resR = op(tree[r--], resR);
        }
        return op(resL, resR);
    }
    
    int findRightMost(int l, const function<bool(T)> &f) const { // f([l:r]) = true인 최대의 r을 찾음, l과 r 둘 다 1-based // 만족하는 r이 없다면 l-1리턴
        assert(1 <= l && l <= n);
        int node = (l - 1) | sz;
        T acc = e();
        
        node >>= __builtin_ctz(node); // node[l, r]에서 l은 그대로 두고 r만 최대한 오른쪽으로 이동
        while (f(op(acc, tree[node]))) {
            acc = op(acc, tree[node++]); // f(node[l, r]) 만족하므로 node+1[r+1, ...]로 이동
            if (!(node & (node - 1))) return n; // node가 2^k꼴 -> 이전의 node-1=2^k-1[l,r=n]꼴
            node >>= __builtin_ctz(node);
        }
        
        while (node < sz) {
            node <<= 1; // node[l, r] -> node*2[l, m]
            if (f(op(acc, tree[node]))) acc = op(acc, tree[node++]); // [m + 1, r]
        }
        return node ^ sz; // f(node)=false인 상황 -> node-1 리턴해야 해야 되서 (node - 1 - sz) -> 1-based로 (node - sz)
    }
    
    int findKthSmallest(int l, T k) const { // query([l, r]) >= k인 최소의 r 찾음, l과 r 둘 다 1-based // 즉, l에서부터 오른쪽으로 k번째 지점 찾는거
        assert(k >= 0);
        return query(l, n) < k ? -1 : findRightMost(l, [&](T sum) { return sum < k; }) + 1;
    }
    
    int findLeftMost(int r, const function<bool(T)> &f) const { // f([l:r]) = true인 최소의 l을 찾음, l과 r 둘 다 1-based // 만족하는 l이 없다면 r+1리턴
        assert(1 <= r && r <= n);
        int node = (r - 1) | sz;
        T acc = e();
    
        node = max(1, node >> __builtin_ctz(~node)); // node[l, r]에서 r은 그대로 두고 l만 최대한 왼쪽으로 이동, 최대로 이동한 게 루트여야 되므로 0이 되면 1로 바꿔줌
        while (f(op(tree[node], acc))) {
            acc = op(tree[node--], acc);  // f(node[l, r]) 만족하므로 node-1[..., l-1]로 이동
            if (!((node + 1) & node)) return n; // node가 2^k-1꼴 -> 이전의 node+1=2^k[l=1,r]꼴이었던 거
            node = max(1, node >> __builtin_ctz(~node));
        }
    
        while (node < sz) {
            node = node << 1 | 1; // node[l, r] -> node*2+1[m+1,r]
            if (f(op(tree[node], acc))) acc = op(tree[node--], acc); // [l, m]
        }
        return node + 2 - sz; // f(node)=false인 상황 -> node+1 리턴해야 해야 되서 (node + 1 - sz) -> 1-based로 (node + 2 - sz)
    }
    
    int findKthLargest(int r, T k) const { // query([l, r]) >= k인 최대의 l 찾음, l과 r 둘 다 1-based // 즉, r에서부터 왼쪽으로 k번째 지점 찾는거
        assert(k >= 0);
        return query(1, r) < k ? -1 : findLeftMost(r, [&](T sum) { return sum < k; }) - 1;
    }
};

/*
findLeftMost(l, f)은 만족하는 r 없는 경우 l-1 리턴   
findRightMost(r, f)은 만족하는 l 없는 경우 r+1 리턴   
findKthSmallest, findKthLargest은 만족하는 값이 없는 경우 -1 리턴   

// ex) 합 세그
int op(const int &a, const int &b) { return a + b; }
int e() { return 0; }
SegmentTree<int, sum, zero> seg(v);
*/