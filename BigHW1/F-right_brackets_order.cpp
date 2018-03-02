#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <string>

int highestOneBit(int x) {
	--x;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x + 1;
}

struct Node {
	int a, b, c; 
	//a - number of pair of brackets in right bracket sequence
	//b - number of left brackets not used in right bracket sequence
	//c - number oа right brackets not used in right bracket sequence 
	Node() : a(0), b(0), c(0) {};
};

class SegmentTree {
public:
	SegmentTree(const std::string & s);
	int query(int, int) const;
	void show_tree() const;
private:
	std::vector<Node> tree;
	int tree_size;
	
	Node make_node(const Node &left, const Node &right) const{
		Node result;
		int new_seq_size = std::min(left.b, right.c);
		result.a = left.a + right.a + new_seq_size;
		result.b = left.b + right.b - new_seq_size;
		result.c = left.c + right.c - new_seq_size;
		return result;
	}
};


SegmentTree::SegmentTree(const std::string & s) {
	int primal_size = s.length();
	tree_size = highestOneBit(primal_size) * 2;
	int start_copy_i = tree_size / 2;
	int finish_copy_i = start_copy_i + primal_size;
	tree.resize(tree_size);
	
	for (int i = start_copy_i; i < finish_copy_i; ++i) {
		Node x;
		if (s[i - start_copy_i] == '(')
			x.b = 1;
		else
			x.c = 1;
		tree[i] = x;
	}
	 
	for (int i = start_copy_i - 1; i > 0; --i) 
		tree[i] = make_node(tree[2 * i], tree[2 * i + 1]);
}

int SegmentTree::query(int first_i, int last_i) const{
	Node left_result;
	Node right_result;
	int shift = tree_size / 2 - 1;
	int l = first_i + shift;
	int r = last_i + shift;
	while (l <= r) {
		if (l & 1)
			left_result = make_node(left_result, tree[l]);
		if (!(r & 1))
			right_result = make_node(tree[r], right_result);
		l = (l + 1) / 2;
		r = (r - 1) / 2;
	}
	Node result = make_node(left_result, right_result);
	return result.a;
}

void SegmentTree::show_tree() const{
	for (int i = 0; i < tree_size; ++i)
		std::cout << '(' << tree[i].a << ", " << tree[i].b << ", " << tree[i].c << "), ";
	std::cout << '\n';
}

int main() {
	int size, n, l, r;
	std::string s;
	std::getline(std::cin, s);
	SegmentTree st(s);
	//st.show_tree();
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> l >> r;
		std::cout << st.query(l, r) * 2 << '\n';
	}
	return 0;
}
