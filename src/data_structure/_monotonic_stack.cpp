vector<int> left_lt(n, -1), left_le(n, -1);
vector<int> left_gt(n, -1), left_ge(n, -1);
vector<int> right_lt(n, n), right_le(n, n);
vector<int> right_gt(n, n), right_ge(n, n);

// left_gt, right_ge
stack<int> s;
for (int i = 0; i < n; i++) {
	while (!s.empty() && v[s.top()] <= v[i]) {
		right_ge[s.top()] = i;
		s.pop();
	}
	if (!s.empty()) left_gt[i] = s.top();
	s.push(i);
}

// left_ge, right_gt
stack<int> s;
for (int i = 0; i < n; i++) {
	while (!s.empty() && v[s.top()] < v[i]) {
		right_gt[s.top()] = i;
		s.pop();
	}
	if (!s.empty()) left_ge[i] = s.top();
	s.push(i);
}

// left_lt, right_le
stack<int> s;
for (int i = 0; i < n; i++) {
	while (!s.empty() && v[s.top()] >= v[i]) {
		right_le[s.top()] = i;
		s.pop();
	}
	if (!s.empty()) left_lt[i] = s.top();
	s.push(i);
}

// left_le, right_lt
stack<int> s;
for (int i = 0; i < n; i++) {
	while (!s.empty() && v[s.top()] > v[i]) {
		right_lt[s.top()] = i;
		s.pop();
	}
	if (!s.empty()) left_le[i] = s.top();
	s.push(i);
}
