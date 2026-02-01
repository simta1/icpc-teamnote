template <typename T>
void compress(vector<T> &orig) { // coordinate_compression // O(N~logN)
    vector<T> v(orig);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (auto &e : orig) e = lower_bound(v.begin(), v.end(), e) - v.begin();
}