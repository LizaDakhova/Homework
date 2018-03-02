#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

vector<int> parent;

int DSU_get(int x) {
	return (parent[x]== x) ? x : (parent[x] = DSU_get(parent[x]));
}

void DSU_unite(int x, int y) {
	x = DSU_get(x);
	y = DSU_get(y);
	if (rand() & 1)
		swap(x, y);
	if (y != x)
		parent[x] = y;
}

int main() {
	int n, m, k, x, y;
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i)
		cin >> x >> y;
		
	vector<pair<char, pair<int, int> > > query(k);
	
	string oper;
	for (int i = 0; i < k; ++i) {
		cin >> oper >> x >> y;
		query[k - i - 1] = make_pair(oper[0], make_pair(x - 1, y - 1));
	}
	
	parent.resize(n);
	for (int i = 0; i < n; ++i)
		parent[i] = i;
		
	vector<bool> result;
	
	for (int i = 0; i < k; ++i) {
		int x = query[i].second.first;
		int y = query[i].second.second;
		if (query[i].first == 'a')
			result.push_back(parent[x] == parent[y]);
		else 
			DSU_unite(x, y);
	}
	
	for (int i = k - m - 1; i >= 0; --i) 
		if (result[i])
			cout << "YES\n";
		else
			cout << "NO\n";
			
	return 0;
}
