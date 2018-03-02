#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

template <typename T>
class ImplissitTreap {
public:
	static T newtral;
	
	struct Node {
		int prior;
		Node * left, * right;
		int size;
		T info;
		T summa;
		
		Node(): left(NULL), right(NULL), size(0), summa(0) {}
		Node(const T & input_info): info(input_info), left(NULL), 
		right(NULL), size(1), summa(input_info) { prior = rand(); }
	};
	
	Node *root;
		
	ImplissitTreap();
	void add(int i, const T &input_val);
	void check_implissitTreap(Node * x);
	void check_node(Node * x);
	
	T sum(int l, int r);
	
	void swapper(ImplissitTreap &odd, ImplissitTreap &even, int l, int r);
	
private:
	int sizeOf(Node * x);
	T sumOf(Node * x);
	void update(Node * x);
	void split(int x, Node * t, Node * & l, Node * & r, int left_size = 0);
	Node * & merge(Node * & l, Node * & r);
};

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
T ImplissitTreap<T>::sum(int l, int r) {
	Node *left, *mid, *right;
	split(l - 1, root, left, mid);
	split(r - l, mid, mid, right);
	T result = sumOf(mid);
	root = merge(left, merge(mid, right));
	return result;
}

template <typename T>
int ImplissitTreap<T>::sizeOf(Node * x) {
	return x ? x->size : 0;
}

template <typename T>
T ImplissitTreap<T>::sumOf(Node * x) {
	return x ? x->summa : 0;
}

template <typename T>
void ImplissitTreap<T>::update(Node * x) {
	if (x)  {
		x->size = sizeOf(x->left) + sizeOf(x->right) + 1;
		x->summa = x->info + sumOf(x->left) + sumOf(x->right);
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

template <typename T>
void ImplissitTreap<T>::swapper(ImplissitTreap &odd, ImplissitTreap &even, int l, int r){
    int l1 = l / 2 + l % 2, l2 = l / 2, r1 = r / 2, r2 = r / 2 - !(r % 2);
    Node *l_mid1, *right1, *left1, *mid1, *l_mid2, *right2, *left2, *mid2;
    split(r1, odd.root, l_mid1, right1);
    split(l1 - 1, l_mid1, left1, mid1);
    split(r2, even.root, l_mid2, right2);
    split(l2 - 1, l_mid2, left2, mid2);	
    l_mid1 = merge(left1, mid2);
    odd.root = merge(l_mid1, right1);
    l_mid2 = merge(left2, mid1);
    even.root = merge(l_mid2, right2);
}

int main() {
    int x, y, n, m, cnt = 1;
    std::cin >> n >> m;
    while (n || m) {
        ImplissitTreap<long long> even_root, odd_root, fictiv;
        std::cout << "Swapper " << cnt++ << ':' << '\n';
        for (int i = 1; i <= n; ++i) {
            std::cin >> x;
            if (i % 2)
                odd_root.add(i - 1, x);
			else
                even_root.add(i - 1, x);
        }
        for (int i = 0; i < m; ++i) {
            std::cin >> x;
            if (x == 1) {
                std::cin >> x >> y;
                --x, --y;
                fictiv.swapper(odd_root, even_root, x, y);
            } 
            else if (x == 2) {
                std::cin >> x >> y;
                --x, --y;
                int l1 = x / 2 + x % 2, l2 = x / 2, r1 = y / 2, r2 = y / 2 - !(y % 2);
                std::cout << odd_root.sum(l1, r1) + even_root.sum(l2, r2) << '\n';
            }
        }
        std::cin >> n >> m;
        std::cout << '\n';
    }
    return 0;
}
