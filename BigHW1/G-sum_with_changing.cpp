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

template <typename T2>
struct BinarySum : std::binary_function <T2, T2, T2> {
	T2 operator() (const T2 &x, const T2 &y) const {
		return x + y;
	}
	static T2 newtral;
};

template <typename T2>
T2 BinarySum<T2>::newtral = 0;

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
	int start_copy_i = tree_size / 2;
	int finish_copy_i = start_copy_i + primal_size;
	
	for (int i = 0; i < tree_size; ++i)
		tree.push_back(oper.newtral);
	
	for (int i = start_copy_i; i < finish_copy_i; ++i)
		tree[i] = v[i - start_copy_i];
		
	for (int i = start_copy_i - 1; i > 0; --i)
		tree[i] = oper(tree[i * 2], tree[i * 2 + 1]);
}

template <template <typename> class Operation, typename T>
T SegmentTree<Operation, T>::query(int first_i, int last_i) const {
	T result = oper.newtral;
	int shift = tree_size / 2 - 1;
	int l = first_i + shift;
	int r = last_i + shift;
	while (l <= r) {
		if (l & 1)
			result = oper(tree[l], result);
		if (!(r & 1))
			result = oper(tree[r], result);
		l = (l + 1) / 2;
		r = (r - 1) / 2;
	}
	return result;
}

template <template <typename> class Operation, typename T>
void SegmentTree<Operation, T>::update(int i, const T &value) {
	int tree_i = i + tree_size / 2 - 1;
	tree[tree_i] = value;
	while (tree_i /= 2)
		tree[tree_i] = oper(tree[tree_i * 2], tree[tree_i * 2 + 1]);
}

template <template <typename> class Operation, typename T>
void SegmentTree<Operation, T>::show_tree() const{
	for (int i = 0; i < tree_size; ++i)
		std::cout << tree[i] << ' ';
	std::cout << '\n';
}



int main() {
	int n1, n2, val, l, r, index, new_val;
	char command;
	std::cin >> n1;
	std::vector<long long> v(n1);
	for (int i = 0; i < n1; ++i) {
		std::cin >> val;
		v[i] = val;
	}
	SegmentTree<BinarySum, long long> st(v);
	std::cin >> n2;
	for (int i = 0; i < n2; ++i) {
		std::cin >> command;
		switch(command) {
			case 's':
				std::cin >> l >> r;
				std::cout << st.query(l, r) << ' ';
				break;
			case 'u':
				std::cin >> index >> new_val;
				st.update(index, new_val);
				break;
		}
	}
	return 0;
}
