//Fenwick or Binary Indeex tree - one- & two-dimensional implementations

#include <iostream>
#include <vector>
#include <stdlib.h>

template <typename T>
struct BinarySum : std::binary_function <T, T, T> {
	T operator() (const T &x, const T &y) const {
		return x + y;
	}
	T reverse (const T &sum, const T &x) const {
		return sum - x;
	}
	static T newtral;
};

template <typename T>
T BinarySum<T>::newtral = 0;

template <template <typename> class Operation, typename T>
class BIT_2 {
public:
	BIT_2(const std::vector<std::vector<T> > &);
	void update(int, int, const T &);
	T oper(int, int, int, int);
	T oper(int, int);
private:
	std::vector<std::vector<T> > tree;
	int size1;
	int size2;
	Operation<T> oper_object;
};

template <template <typename> class Operation, typename T>
BIT_2<Operation, T>::BIT_2(const std::vector<std::vector<T> > &v) {
	size1 = v.size();
	size2 = v[0].size();
	tree.resize(size1);
	for (int i = 0; i < size1; ++i) {
		tree[i].resize(size2);
		for (int j = 0; j < size2; ++j)
			tree[i][j] = oper_object.newtral;
	}
	for (int i = 0; i < size1; ++i) {
		for (int j = 0; j < size2; ++j)
			update (i, j, v[i][j]);
	}
}

template <template <typename> class Operation, typename T>
void BIT_2<Operation, T>::update(int index1, int index2, const T &val) {
	//T dif = oper_object.reverse(val, oper(index1, index2, index1, index2));
	for (int x = index1; x < size1; x = x | (x + 1))
		for (int y = index2; y < size2; y = y | (y + 1))
			tree[x][y] = oper_object(tree[x][y], val);
} 

template <template <typename> class Operation, typename T>
T BIT_2<Operation, T>::oper(int x, int y) {
	T result = oper_object.newtral;
	for (int i = x; i >= 0; i = (i & (i + 1)) - 1) 
		for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
			result = oper_object(result, tree[i][j]);
	return result;
}

template <template <typename> class Operation, typename T>
T BIT_2<Operation, T>::oper(int x1, int y1, int x2, int y2) {
	if (x1 && y1) {
		T temp = oper_object.reverse(oper(x2, y2),oper(x1 - 1, y2));
		temp = oper_object.reverse(temp, oper(x2, y1 - 1));
		temp = oper_object(temp, oper(x1 - 1, y1 - 1));
		return temp;
	}
	else if (x1)
		return oper_object.reverse(oper(x2, y2), oper(x1 - 1, y2));
	else if (y1)
		return oper_object.reverse(oper(x2, y2), oper(x2, y1 - 1));
	else
		return oper(x2, y2);
}

int main() {
	int n, m, k, command, x1, y1, x2, y2, val; 
	std::cin >> n >> m;
	std::vector<std::vector<long long> > v;
	v.resize(n);
	for (int i = 0; i < n; ++i) {
		v[i].resize(m);
		for (int j = 0; j < m; ++j)
			v[i][j] = 0;
	}
	BIT_2<BinarySum, long long> bit2(v);
	
	std::cin >> k;
	for (int i = 0; i < k; ++i) {
		std::cin >> command;
		switch (command) {
			case 2:
				std::cin >> x1 >> y1 >> x2 >> y2;
				std::cout << bit2.oper(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << '\n';
				break;
			case 1:
				std::cin >> x1 >> y1 >> val;
				
				bit2.update(x1 - 1, y1 - 1, val);
				break;
		}
	}
	
	return 0;
}
