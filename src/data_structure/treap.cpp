struct Node {
	int value;

    inline static mt19937 rng;
	int priority, size;
	Node *par = nullptr;
	Node *left = nullptr, *right = nullptr;
	Node(int value): value(value), priority(rng()), size(1) {}
	void push_up() { // need push down
		size = 1;
		if (right) { size += right->size; }
		if (left) { size += left->size; }
	}
	~Node() {
		if (left) delete left;
		if (right) delete right;
	}
};
pair<Node*, Node*> split(Node *root, int k) { // k, residue, push_down
	if (root == nullptr) return {nullptr, nullptr};
	int left_size = root->left ? root->left->size : 0;
	if (left_size + 1 <= k) {
		auto r_sub = split(root->right, k - left_size - 1);
		root->right = r_sub.first;
		if (r_sub.first) r_sub.first->par = root;
		root->push_up();
		return {root, r_sub.second};
	} else {
		auto l_sub = split(root->left, k);
		root->left = l_sub.second;
		if (l_sub.second) l_sub.second->par = root;
		root->push_up();
		return {l_sub.first, root};
	}
}
Node* merge(Node *a, Node *b) { // a then b, push_down
	if (!a) return b;
	if (!b) return a;
	if (a->priority < b->priority) {
		Node *t = b->left = merge(a, b->left);
		if (t) t->par = b;
		b->push_up();
		return b;
	} else {
		Node *t = a->right = merge(a->right, b);
		if (t) t->par = a;
		a->push_up();
		return a;
	}
}
int get_index(Node *a) { // 0-based, push_down
	int ret = a->left ? a->left->size : 0;
	while (a->par) {
		if (a->par->right == a) {
			ret += 1 + (a->par->left ? a->par->left->size : 0);
		}
		a = a->par;
	}
	return ret;
}