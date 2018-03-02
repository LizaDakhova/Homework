#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>
#include <string>

int big_rand() {
	return (rand() * rand());
}

template <typename T>
class Treap {
public:
	struct Node {
		T key;
		int prior;
		Node *left, *right;
		T summa;
		int size;
		
		Node(): left(NULL), right(NULL), size(0), summa(0) {}
		Node(const T & input_key): key(input_key),
		left(NULL), right(NULL), size(0), summa(input_key) {
			prior = big_rand();
		}
	};
		
	Treap(): root(NULL) {};
	//~Treap();
		
	void insert(const T & val);
	void delete_node(const T & val);
	
	bool exists(const T & val) const;
	Node* search(const T &val) const;
	Node* search(Node *x, const T &val) const;
	
	//----------------------------------------
	
	T sum(const T & l, const T & r);
	Node* k_element(int k);
	void show_k_element(int k);
		
private:
	Node *root;
	std::set<T> values;
	T sumOf(Node * x);
	int sizeOf(Node * x);
	void update(Node * x);
	void split(Node *t, const T & skey, Node * &l, Node * &r);
	Node* & merge(Node *&l, Node *&r); 
};

/*template <typename T>
Treap<T>::~Treap() {
	int size = values.size();
	for (typename std::set<T>::iterator it = values.begin(); it != values.end(); ++it)
		delete_node(*it);
}*/

template <typename T>
T Treap<T>::sumOf(Node * x) {
	return x ? x->summa : 0;
}

template <typename T>
int Treap<T>::sizeOf(Node * x) {
	return x ? x->size : 0;
}

template <typename T>
void Treap<T>::update(Node * x) {
	if (x)  {
		x->summa = sumOf(x->left) + sumOf(x->right) + x->key;
		x->size = sizeOf(x->left) + sizeOf(x->right) + 1;
	}
}

template <typename T>
void Treap<T>::split(Node *t, const T &skey, Node * &l, Node * &r) {
	if (!t) 
		l = r = NULL;
	else
	
		if (t->key > skey) {
			split(t->left, skey, l, t->left);
			r = t;
		}
		else {
			split(t->right, skey, t->right, r);
			l = t;
		}	
	update(t);
}

template <typename T>
typename Treap<T>::Node * & Treap<T>::merge(Node * & l, Node * & r) {
	if (!l || !r)
		return l ? l : r;
	else if (l->prior >= r->prior) {
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
void Treap<T>::insert(const T & val) {
	values.insert(val);
	Node *l, *r;
	Node* newnode = new Node(val);
	split(root, val, l, r);
	root = merge(l, merge(newnode, r));
	
}

template <typename T>
void Treap<T>::delete_node(const T & val) {
	if (search(val)) {
		values.erase(val);
		Node *l, *r, *mid;
		split(root, val - 1, l, r);
		split(r, val, mid, r);
		root = merge(l, r);
	}
}


template <typename T>
bool Treap<T>::exists(const T & val) const {
	if (search(val))
		return true;
	else
		return false;
}

template <typename T>
typename Treap<T>::Node* Treap<T>::search(const T &val) const {
	return search(root, val);
}

template <typename T>
typename Treap<T>::Node* Treap<T>::search(Node *x, const T &val) const {
	if (x == NULL || x->key == val) {
		return x;
	}
	else {
		if (x->key < val)
			return search(x->right, val);
		else
			return search(x->left, val);
	}
}


template <typename T>
T Treap<T>::sum(const T & l, const T & r) {
	Node *left, *mid, *right;
	split(root, l - 1, left, right);
	split(right, r, mid, right);
	T result = sumOf(mid);
	root = merge(left, merge(mid, right));
	return result;
}

template <typename T>
typename Treap<T>::Node* Treap<T>::k_element(int k) {
	Node *x = root;
	while (x) {
		int size_left = sizeOf(x->left);
		if (size_left == k)
			return x;
		x = size_left > k ? x->left : x->right;
		if (size_left < k) 
			k -= size_left + 1;
	}
	return NULL;	
}

template <typename T>
void Treap<T>::show_k_element(int k) {
	Node *x = k_element(k);
	if (x)
		std::cout << x->key << '\n';
	else
		std::cout << "none\n";
}
	
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, val, l, r, x;
	long long ans_res = 0;
	bool flag = false;
	char c;
	Treap<long long> s;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> c;
		if (c == '+') {
			std::cin >> x;
			if (flag) {
				val = (x + ans_res) % 1000000000;
				if (!s.exists(val))
					s.insert(val);
				flag = false;
			}
			else {
				if (!s.exists(x))
					s.insert(x);
			}
		} 
		else if (c == '?') {
			flag = true;
			std::cin >> l >> r;
			ans_res = s.sum(l, r);
			std::cout << ans_res << '\n';
		}
	}
	return 0;
}
