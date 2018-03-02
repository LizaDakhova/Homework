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
class BIT_3 {
public:
	std::vector<std::vector<std::vector<T> > > tree;
	BIT_3(int n, int m, int p);
	void update(int, int, int, const T &);
	T oper(int, int, int, int, int, int);
	T oper(int, int, int);
private:
	
	int size1;
	int size2;
	int size3;
	Operation<T> oper_object;
};

template <template <typename> class Operation, typename T>
BIT_3<Operation, T>::BIT_3(int n, int m, int p) {
	size1 = n;
	size2 = m;
	size3 = p;
	tree.resize(size1);
	for (int i = 0; i < size1; ++i) {
		tree[i].resize(size2);
		for (int j = 0; j < size2; ++j) {
			tree[i][j].resize(size3);
			for (int k = 0; k < size3; ++k)
				tree[i][j][k] = oper_object.newtral;
		}
	}
}

template <template <typename> class Operation, typename T>
void BIT_3<Operation, T>::update(int index1, int index2, int index3, const T &val) {
	//T dif = oper_object.reverse(val, oper(index1, index2, index1, index2));
	for (int x = index1; x < size1; x = x | (x + 1))
		for (int y = index2; y < size2; y = y | (y + 1))
			for (int z = index3; z < size3; z = z | (z + 1))
				tree[x][y][z] = oper_object(tree[x][y][z], val);
} 

template <template <typename> class Operation, typename T>
T BIT_3<Operation, T>::oper(int x, int y, int z) {
	T result = oper_object.newtral;
	for (int i = x; i >= 0; i = (i & (i + 1)) - 1) 
		for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
			for (int k = z; k >= 0; k = (k & (k + 1)) - 1)
				result = oper_object(result, tree[i][j][k]);
	return result;
}

template <template <typename> class Operation, typename T>
T BIT_3<Operation, T>::oper(int x1, int y1, int z1, int x2, int y2, int z2) {
	T oper_big_temps = oper_object(oper_object(oper(x1 - 1, y2, z2), 
	oper(x2, y1 - 1, z2)), oper(x2, y2, z1 - 1));
	T oper_all_big_temps = oper_object.reverse(oper(x2, y2, z2), oper_big_temps);
	T oper_small_temps = oper_object(oper_object(oper(x2, y1 - 1, z1 - 1), 
	oper(x1 - 1, y2, z1 - 1)), oper(x1 - 1, y1 - 1, z2));
	T oper_all_small_temps = oper_object.reverse(oper_small_temps, oper(x1 - 1, y1 - 1, z1 - 1));
	return oper_object(oper_all_big_temps, oper_all_small_temps);
}

int main() {
	int n, command, x1, y1, z1, x2, y2, z2, val; 
	std::cin >> n;
	BIT_3<BinarySum, long long> bit3(n, n, n);
	
	std::cin >> command;
	while (command != 3) {
		switch (command) {
			case 2:
				std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
				std::cout << bit3.oper(x1, y1, z1, x2, y2, z2) << '\n';
				break;
			case 1:
				std::cin >> x1 >> y1 >> z1 >> val;
				
				bit3.update(x1, y1, z1, val);
				break;
		}
		std::cin >> command;
	}
	
	return 0;
}
