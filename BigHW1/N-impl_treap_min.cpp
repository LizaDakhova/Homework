#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

int big_rand() {
	return (rand() * rand());
}

template <typename T>
class ImplissitTreap : std::binary_function <T, T, T> {
public:
	static T newtral;
	
	struct Node {
		int prior;
		Node * left, * right;
		int size;
		T info;
		T minimum;
		
		Node(): left(NULL), right(NULL), size(0), minimum(newtral) {}
		Node(const T & input_info): info(input_info), left(NULL), 
		right(NULL), size(1), minimum(input_info) { prior = big_rand(); }
	};
	
	Node *root;
		
	ImplissitTreap();
	void add(int i, const T &input_val);
	void check_implissitTreap(Node * x);
	void check_node(Node * x);
	
	T min(int l, int r);
private:
	int sizeOf(Node * x);
	T minOf(Node * x);
	void update(Node * x);
	void split(int x, Node * t, Node * & l, Node * & r, int left_size = 0);
	Node * & merge(Node * & l, Node * & r);
};

template <typename T>
T ImplissitTreap<T>::newtral = std::numeric_limits<T>::max();

template <typename T>
ImplissitTreap<T>::ImplissitTreap() {
	root = NULL;
}

template <typename T>
void ImplissitTreap<T>::check_node(Node * x) {
	std::cout << "node is " << x->info << '\n';
}

template <typename T>
void ImplissitTreap<T>::check_implissitTreap(Node * x) {
	if (x) {
		check_implissitTreap(x->left);
		std::cout << x->info << ' ';
		check_implissitTreap(x->right);
	}
}

template <typename T>
T ImplissitTreap<T>::min(int l, int r) {
	Node *left, *mid, *right;
	split(l - 1, root, left, mid);
	split(r - l, mid, mid, right);
	T result = minOf(mid);
	root = merge(left, merge(mid, right));
	return result;
}

template <typename T>
int ImplissitTreap<T>::sizeOf(Node * x) {
	return x ? x->size : 0;
}

template <typename T>
T ImplissitTreap<T>::minOf(Node * x) {
	return x ? x->minimum : newtral;
}

template <typename T>
void ImplissitTreap<T>::update(Node * x) {
	if (x)  {
		x->size = sizeOf(x->left) + sizeOf(x->right) + 1;
		x->minimum = std::min(x->info, std::min(minOf(x->left), minOf(x->right)));
	}
}

template <typename T>
void ImplissitTreap<T>::split(int x, Node * t, Node * & l, Node * & r, int left_size) {
	if (!t) {
		l = r = NULL; 
		return;
	}
	int i = left_size + sizeOf(t->left);
	if (i <= x) {
		split(x, t->right, t->right, r, i + 1);
		l = t;
	}
	else {
		split(x, t->left, l, t->left, left_size);
		r = t;
	}
	update(t);
}

template <typename T>
typename ImplissitTreap<T>::Node * & ImplissitTreap<T>::merge(Node * & l, Node * & r) {
	if (!l || !r)
		return l ? l : r;
	else if (l->prior > r->prior) {
		l->right = merge(l->right, r);
		update(l);
		return l;
	}
	else {
		r->left = merge(l, r->left);
		update(r);
		return r;
	}
}

template <typename T>
void ImplissitTreap<T>::add(int i, const T & input_info) {
	Node *new_node = new Node(input_info);
	Node *l = NULL, *r = NULL;
	split(i, root, l, r);
	root = merge(l, merge(new_node, r)); 
}

int main() {
	ImplissitTreap<int> itreap;
	int n, index, val, l, r;
	char c;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> c;
		switch(c) {
			case '+':
				std::cin >> index >> val;
				itreap.add(index - 1, val);
				break;
			case '?':
				std::cin >> l >> r;
				std::cout << itreap.min(l - 1, r - 1) << '\n';
				break;
		}
	}
	return 0;
}
