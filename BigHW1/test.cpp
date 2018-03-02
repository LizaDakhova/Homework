#include <iostream>
#include <cstdlib>

using namespace std;

struct Treap {
int prior;
int size;
long long data;
long long min;
long long add;
bool reverse;
Treap *l, *r;
Treap (long long data): data(data), prior(rand()), size(1), l(NULL), r(NULL), min(data), reverse(false), add(0) {}
};

typedef Treap* Treap_ptr;

int sz(Treap_ptr v) {
return (v == NULL) ? 0 : v->size;
}

void update(Treap_ptr v) {
if (v != NULL) {
v->size = 1 + sz(v->l) + sz(v->r);
}
}

void split(Treap_ptr root, int x, Treap_ptr &L, Treap_ptr &R) {
if (root == NULL) {
L = NULL;
R = NULL;
return;
}
if (root -> data <= x) {
L = root;
split(root->r, x, root-> r, R);
} else {
R = root;
split(root->l, x, L, root->l);
}
update(root);
}

Treap_ptr merge(Treap_ptr L, Treap_ptr R) {
if (L == NULL) {
update(R);
return R;
} else if (R == NULL) {
update(L);
return L;
}
if (L->prior >= R->prior) {
L->r = merge(L->r, R);
update(L);
return L;
} else {
R->l = merge(L, R->l);
update(R);
return R;
}
}

void insert(Treap_ptr &root, int new_data) {
Treap_ptr left, right;
Treap_ptr new_v = new Treap(new_data);
split(root, new_data, left, right);
root = merge(left, merge(new_v, right));
}

void erase(Treap_ptr &root, int x) {
Treap_ptr left, right, mid = NULL;
split(root, x - 1, left, right);
split(right, x, mid, right);
root = merge(left, right);
update(root);
}

bool exists(Treap_ptr &root, int x) {
if (root == NULL) {
return false;
} else {
if (x == root -> data) {
return true;
}
if (x > root -> data) {
return exists(root -> r, x);
} else {
return exists(root -> l, x);
}
}
}

void kth(Treap_ptr &root, int k) {
Treap_ptr tmp = root;
while (tmp != NULL) {
int size_l = sz(tmp->l);
if (size_l == k) {
cout << tmp->data << '\n';
return;
}
tmp = size_l > k ? tmp -> l : tmp -> r;
if (size_l < k) {
k -= size_l + 1;
}
}
cout << "none" << '\n';
}

void next(Treap_ptr &root, int x) {
Treap_ptr left, right;
split(root, x, left, right);
Treap_ptr tmp = right;
while (tmp != NULL) {
if (tmp -> l == NULL) {
cout << tmp -> data << '\n';
return;
}
tmp = tmp -> l;
}
cout << "none" << '\n';
}

void prev(Treap_ptr &root, int x) {
Treap_ptr left, right;
split(root, x - 1, left, right);
Treap_ptr tmp = left;
while (tmp != NULL) {
if (tmp -> r == NULL) {
cout << tmp -> data << '\n';
return;
}
tmp = tmp -> r;
}
cout << "none" << '\n';
}

Treap_ptr root = NULL;

int main() {
int x;
string s;
while (cin >> s >> x) {
if (s == "insert") {
insert(root, x);
} else if (s == "delete") {
erase(root, x);
} else if (s == "exists") {
if (exists(root, x)) {
cout << "true" << '\n';
} else {
cout << "false" << '\n';
}
} else if (s == "next") {
next(root, x);
} else if (s == "prev") {
prev(root, x);
} else if (s == "kth") {
kth(root, --x);
}
}
return 0;
}

