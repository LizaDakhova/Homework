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
struct BinaryMax : std::binary_function <T, T, T> {
	T operator() (const T &x, const T &y) const {
		return std::max(x, y);
	}
	static T newtral; 
};

template <typename T>
T BinaryMax<T>::newtral = std::numeric_limits<T>::min();

template <template <typename> class Operation, typename T>
class SegmentTree {
public:
	SegmentTree(const std::vector<T> &);
	std::pair<T, int> query(int l, int r) const;
	void update(int, const T &);
	void show_tree() const;
private:
	std::vector<std::pair<T, int> > tree;
	int tree_size;
	Operation<T> oper;
	
	std::pair<T, int> choice(const std::pair<T, int> & left, const std::pair<T, int> & right) const;
};

template <template <typename> class Operation, typename T>
SegmentTree<Operation, T>::SegmentTree(const std::vector<T> &v) {
	int primal_size = v.size();
	tree_size = highestOneBit(primal_size) * 2;
	int start_copy_i = tree_size / 2;
	int finish_copy_i = start_copy_i + primal_size;

	for (int i = 0; i < tree_size; ++i)
		tree.push_back(std::make_pair(oper.newtral, 1));
	
	for (int i = start_copy_i; i < finish_copy_i; ++i)
		tree[i].first = v[i - start_copy_i];
	
	for (int i = start_copy_i - 1; i > 0; --i)
		tree[i] = choice(tree[i * 2], tree[i * 2 + 1]);
}

template <template <typename> class Operation, typename T>
std::pair<T, int> SegmentTree<Operation, T>::query(int first_i, int last_i) const {
	std::pair<T, int> result(oper.newtral, 1);
	int shift = tree_size / 2 - 1;
	int l = first_i + shift;
	int r = last_i + shift;
	
	while (l <= r) {
		if (l & 1) 
			result = choice(result, tree[l]);
		if (!(r & 1)) 
			result = choice(result, tree[r]);
		l = (l + 1) / 2;
		r = (r - 1) / 2;
	}
	return result;
}

template <template <typename> class Operation, typename T>
void SegmentTree<Operation, T>::show_tree() const{
	for (int i = 0; i < tree_size; ++i) {
		std::cout << '(' << tree[i].first << ", " << tree[i].second << "); ";
	}
	std::cout << '\n';
}

template <template <typename> class Operation, typename T>
std::pair<T, int> SegmentTree<Operation, T>::choice(const std::pair<T, int> & left, const std::pair<T, int> & right) const {
	std::pair<T, int> result;
	result.first = oper(left.first, right.first);
	if (result.first == left.first && result.first == right.first)
		result.second = left.second + right.second;
	else if (result.first == left.first)
		result.second = left.second;
	else if (result.first == right.first)
		result.second = right.second;
	return result;
}

int main() {
	int n1, n2, val, l, r, maximum;
	
	std::cin >> n1;
	std::vector<int> v(n1);
	for (int i = 0; i < n1; ++i) {
		std::cin >> val;
		v[i] = val;
	}
	
	std::pair<int, int> result;
	SegmentTree<BinaryMax, int> st(v);
	//st.show_tree();
	std::cin >> n2;
	for (int i = 0; i < n2; ++i) {
		std::cin >> l >> r;
		result = st.query(l, r);
		std::cout << result.first << ' ' << result.second << '\n';
	}
	return 0;
}
	
