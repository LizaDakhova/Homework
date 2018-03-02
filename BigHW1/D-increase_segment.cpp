#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

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
struct BinaryAdd : std::binary_function <T, T, T> {
	T operator() (const T &x, const T & add_val) const {
		return x + add_val;
	}
	static T newtral;
};

template <typename T>
T BinaryAdd<T>::newtral = 0;

template <template <typename> class Operation, typename T>
class SegmentTree {
public:
	SegmentTree(const std::vector<T> &);
	void query(int first_i, int last_i, const T & add_val);
	void update(int, const T &);
	T i_value(int i);
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
	int start_copy_i = tree_size / 2;
	int finish_copy_i = start_copy_i + primal_size;
	
	for (int i = 0; i < tree_size; ++i)
		tree.push_back(oper.newtral);
	
	for (int i = start_copy_i; i < finish_copy_i; ++i)
		tree[i] = v[i - start_copy_i];
}

template <template <typename> class Operation, typename T>
void SegmentTree<Operation, T>::query(int first_i, int last_i, const T & add_val) {
	int shift = tree_size / 2 - 1;
	int l = first_i + shift;
	int r = last_i + shift;
	while (l <= r) {
		if (l & 1) {
			tree[l] = oper(tree[l], add_val);
		}
		if (!(r & 1)) {
			tree[r] = oper(tree[r], add_val);
		}
		l = (l + 1) / 2;
		r = (r - 1) / 2;
	}
}

template <template <typename> class Operation, typename T>
T SegmentTree<Operation, T>::i_value(int i) {
	int real_i = i + tree_size / 2 - 1;
	T result = tree[real_i];
	for (real_i; real_i > 1; real_i = real_i / 2)
		result = oper(result, tree[real_i / 2]);
	return result;
}

template <template <typename> class Operation, typename T>
void SegmentTree<Operation, T>::show_tree() const {
	for (int i = 0; i < tree_size; ++i)
		std::cout << tree[i] << ' ';
	std::cout << '\n';
}



int main() {
	int n1, n2, val, i, l, r, add_val;
	char command;
	
	std::cin >> n1;
	std::vector<long long> v(n1);
	for (int j = 0; j < n1; ++j) {
		std::cin >> val;
		v[j] = val;
	}
	SegmentTree<BinaryAdd, long long> st(v);
	
	std::cin >> n2;
	for (int j = 0; j < n2; ++j) {
		std::cin >> command;
		if (command == 'g') {
			std::cin >> i;
			std::cout << st.i_value(i) << '\n';
		}
		else if (command == 'a') {
			std::cin >> l >> r >> add_val;
			st.query(l, r, add_val);
		}
	}
	return 0;
}
