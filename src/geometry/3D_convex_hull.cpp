// naive O(N^4)
template <typename T>
bool isExtreme(const vector<Point3D<T>> &ps, const Point3D<T> &p1, const Point3D<T> &p2, const Point3D<T> &p3) {
	auto normal = cross(p2 - p1, p3 - p1);
	if (normal.x == 0 && normal.y == 0 && normal.z == 0) return false; // collinear
	int cntPos = 0, cntNeg = 0;
	for (auto point : ps) {
		cntPos += (dot(normal, point - p1) > 0);
		cntNeg += (dot(normal, point - p1) < 0);
	}
	return cntPos == 0 || cntNeg == 0;
}
template <typename T>
vector<tuple<int, int, int>> getConvexHullFaceIdxes(const vector<Point3D<T>> &ps) {
	vector<tuple<int, int, int>> res;
	int n = ps.size();
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			for (int k = j + 1; k < n; ++k) {
				if (isExtreme(ps, ps[i], ps[j], ps[k])) res.emplace_back(i, j, k);
			}
		}
	}
	return res;
}

// incremental $O(N^2)$
template <typename T>
bool collinear(const Point3D<T> &p1, const Point3D<T> &p2, const Point3D<T> &p3) {
	auto [x, y, z] = cross(p2 - p1, p3 - p1);
	return abs(x) <= 1e-9 && abs(y) <= 1e-9 && abs(z) <= 1e-9;
}
template <typename T>
vector<tuple<int, int, int>> getConvexHullFaceIdxes(vector<Point3D<T>> ps) {
	int n = ps.size();
	assert(n >= 3);
	sort(ps.begin(), ps.end());
	vector<tuple<int, int, int>> res;
	vector<vector<bool>> edgeVisible(n, vector<bool>(n, true));
	auto add = [&ps, &res, &edgeVisible](int a, int b, int c) {
		res.emplace_back(a, b, c);
		edgeVisible[a][b] = edgeVisible[b][c] = edgeVisible[c][a] = false;
	};
	for (int i = 2; i < n; i++) if (!collinear(ps[0], ps[1], ps[i])) {
		swap(ps[2], ps[i]);
		break;
	}
	assert(!collinear(ps[0], ps[1], ps[2]) && "모든 점들이 한 직선 위에 있음");
	add(0, 1, 2);
	add(0, 2, 1);
	for(int i = 3; i < n; i++) {
		vector<tuple<int, int, int>> invisibleFaces;
		for(auto [idx1, idx2, idx3] : res) {
			Point3D<T> normal = cross(ps[idx2] - ps[idx1], ps[idx3] - ps[idx1]);
			if(dot(normal, ps[i] - ps[idx1]) > 1e-9) edgeVisible[idx1][idx2] = edgeVisible[idx2][idx3] = edgeVisible[idx3][idx1] = true;
			else invisibleFaces.emplace_back(idx1, idx2, idx3);
		}
		res.clear();
		for(auto [idx1, idx2, idx3] : invisibleFaces) {
			if(edgeVisible[idx2][idx1]) add(idx2, idx1, i);
			if(edgeVisible[idx3][idx2]) add(idx3, idx2, i);
			if(edgeVisible[idx1][idx3]) add(idx1, idx3, i);
		}
		res.insert(res.end(), invisibleFaces.begin(), invisibleFaces.end());
	}
	return res;
}