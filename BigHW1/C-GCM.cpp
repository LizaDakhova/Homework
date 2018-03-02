#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

template <typename T>
T GCM(T x, T y) {
	while (x && y)
		if (x > y) 
			x %= y;
		else
			y %= x;
	return x + y;
}

int highestOneBit(int x) {
	--x;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x + 1;
 }

template <typename T>
struct BinaryGCM : std::binary_function <T, T, T> {
	T operator() (const T &x, const T &y) const {
		return GCM(x, y);
	}
	static T newtral;
};

template <typename T>
T BinaryGCM<T>::newtral = 1;

template <template <typename> class Operation, typename T>
class SegmentTree {
public:
	SegmentTree(const std::vector<T> &);
	T query(int, int) const;
	void update(int, const T &);
	void show_tree() const;
private:
	std::vector<T> tree;
	int tree_size;
	Operation<T> oper;
};

template <template <typename> class Operation, typename T>
SegmentTree<Operation, T>::SegmentTree(const std::vector<T> &v) {
	int primal_size = v.size();
	tree_size = highestOneBit(primal_size) * 2;
	//std::cout << "tree_size " << tree_size << '\n';
	
	int start_copy_i = tree_size / 2;
	int finish_copy_i = start_copy_i + primal_size;
	
	//filling tree with inf
	for (int i = 0; i < tree_size; ++i) {
		tree.push_back(oper.newtral);
	}
	
	//copying from input vector v
	for (int i = start_copy_i; i < finish_copy_i; ++i) {
		tree[i] = v[i - start_copy_i];
	}
	
	//filling tree
	for (int i = start_copy_i - 1; i > 0; --i) {
		tree[i] = oper(tree[i * 2], tree[i * 2 + 1]);
	}
}

template <template <typename> class Operation, typename T>
T SegmentTree<Operation, T>::query(int first_i, int last_i) const {
	int shift = tree_size / 2 - 1;
	int l = first_i + shift;
	int r = last_i + shift;
	T result = tree[l];
	while (l <= r) {
		if (l & 1) {
			result = oper(tree[l], result);
		}
		if (!(r & 1)) {
			result = oper(tree[r], result);
		}
		l = (l + 1) / 2;
		r = (r - 1) / 2;
	}
	return result;
}

template <template <typename> class Operation, typename T>
void SegmentTree<Operation, T>::update(int i, const T &value) {
	int tree_i = i + tree_size / 2 - 1;
	tree[tree_i] = value;
	while (tree_i /= 2) {
		tree[tree_i] = oper(tree[tree_i * 2], tree[tree_i * 2 + 1]);
	}
}

template <template <typename> class Operation, typename T>
void SegmentTree<Operation, T>::show_tree() const{
	for (int i = 0; i < tree_size; ++i) {
		std::cout << tree[i] << ' ';
	}
	std::cout << '\n';
}



int main() {
	int n1, val, n2, l, r;
	std::cin >> n1;
	std::vector<int> v(n1);
	for (int i = 0; i < n1; ++i) {
		std::cin >> val;
		v[i] = val;
	}
	SegmentTree<BinaryGCM, int> st(v);
	//st.show_tree();
	std::cin >> n2;
	for (int i = 0; i < n2; ++i) {
		std::cin >> l >> r;
		std::cout << st.query(l, r) << '\n';
	}
	return 0;
}
