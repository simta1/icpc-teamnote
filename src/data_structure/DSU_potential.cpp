template <typename T>
class DisjointSet {
private:
    vector<int> parent;
    vector<T> weight;

    int find(int a) {
        if (parent[a] == a) return a;
        find(parent[a]); // calculate weight[parent[a]]
        weight[a] += weight[parent[a]];
        return parent[a] = find(parent[a]);
    }

public:
    DisjointSet(int n) : parent(n + 1), weight(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    void merge(int a, int b, T w) { // b = a + w
        int ra = find(a);
        int rb = find(b);

        if (ra > rb) {
            swap(ra, rb);
            swap(a, b);
            w *= -1;
        }

        weight[rb] = weight[a] + w - weight[b];
        parent[rb] = ra;
    }

    bool isConnected(int a, int b) {
        return find(a) == find(b);
    }

    T getDiff(int a, int b) {
        return weight[b] - weight[a];
    }
};
// !isConnected(a, b)라면 a와 b를 비교할 수 없음.
// getDiff쓰기 전에 isConnected(a, b)인지 확인하고 써야 됨
