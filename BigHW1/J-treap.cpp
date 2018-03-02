#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Treap {
public:
	struct Node {
		T key;
		int prior;
		int number;
		Node *father, *left, *right;
		
		Node(): father(NULL), left(NULL), right(NULL) {}
		Node(const T & input_key, int input_prior, int input_number): 
		key(input_key), prior(input_prior), number(input_number), 
		father(NULL), left(NULL), right(NULL) {}
	};
	
	Treap(const std::vector<std::pair<T, int> > & v);
	void insert(const T & input_key, int input_prior, int input_number);
	void walk_treap() const;
	~Treap();
private:
	Node *root;
	std::vector<Node *> nodes;
	void split(Node *t, const T & skey, Node * &l, Node * &r);
};

bool comp(Treap<int>::Node* x, Treap<int>::Node* y) {
	return x -> key < y -> key;
}

template <typename T>
Treap<T>::Treap(const std::vector<std::pair<T, int> > & v0) {
	//sort the vector, make its parametrs
	std::vector<std::pair<T, int> > v = v0;
	std::vector<Node*> nodes_sorted;
	int size = v.size();
	for (int i = 0; i < size; ++i) {
		Node* temp_node = new Node(v[i].first, v[i].second, i+1);
		nodes.push_back(temp_node);
		nodes_sorted.push_back(temp_node);
	}
	sort(nodes_sorted.begin(), nodes_sorted.end(), comp);
	
	//make a node for start, it is names temp_node
	root = nodes_sorted[0];
	Node* temp_node = root;
	//a cycle
	for (int i = 1; i < size; ++i) {
		//create a node(next_node) that is compared with temp_node
		Node *next_node = nodes_sorted[i];
		
		
		if (temp_node->prior < next_node->prior) {
			//in this ocasion the next_node has to be the only right child of temp_node
			temp_node->right = next_node;
			next_node->father = temp_node;
		}
		else { 
			//in this ocasion the first node having higher prior should 
			//be found and it will become the father for next_node, 
			//while this one becomes its right child, and previous right 
			//child becomes ones left child, otherwise the next_node
			//should become a root, having the highest node as a left 
			//child
			while (temp_node->father && temp_node->prior >= next_node->prior)
				temp_node = temp_node->father;
			if (!temp_node->father && temp_node->prior >= next_node->prior) { //temp_node == root
				temp_node->father = next_node;
				next_node->left = temp_node;
				root = next_node;
			}
			else {
				next_node->left = temp_node->right;
				temp_node->right = next_node;
				next_node->father = temp_node;
				next_node->left->father = next_node;
			}
		}
		temp_node = next_node;
	}
}


template <typename T>
Treap<T>::~Treap(){
	Node *x = root;
	while (x)
		if (x->left)
			x = x->left;
		else if (x->right)
			x = x->right;
		else {
			Node *buf = x->father;
			if (buf && (x == buf->left))
				buf->left = NULL;
			else if (buf)
				buf->right = NULL;
			delete x;
			x = buf;
		}
}


template <typename T>
void Treap<T>::walk_treap() const {
	int size = nodes.size();
	for (int i = 0; i < size; ++i)
		std::cout << (nodes[i]->father ? nodes[i]->father->number : 0) << ' '
		<< (nodes[i]->left ? nodes[i]->left->number : 0) << ' '
		<< (nodes[i]->right ? nodes[i]->right->number : 0) << '\n';
}

int main() {
	int n, a_i, b_i;
	std::cin >> n;
	std::vector<std::pair<int, int> > v;
	for (int i = 0; i < n; ++i) {
		std::cin >> a_i >> b_i;
		v.push_back(std::make_pair(a_i, b_i));
	}
	Treap<int> treap(v);
	std::cout << "YES\n";
	treap.walk_treap();
	return 0;
}

