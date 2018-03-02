#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;
vector<int> parent;
vector <int> weight;

int DSU_get(int x) {
	return (parent[x]== x) ? x : (parent[x] = DSU_get(parent[x]));
}

void DSU_unite(int x, int y, int w) {
	x = DSU_get(x);
	y = DSU_get(y);
	if (rand() & 1)
		swap(x, y);
	if (y != x) {
		parent[x] = y;
		weight[y] += w + weight[x];
	} else
		weight[x] += w;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k, command, x, y, w;
	cin >> n >> m;
	parent.resize(n);
	weight.resize(n);
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		weight[i] = 0;
	}
		
	for (int i = 0; i < m; i++) {
		cin >> command;
		if (command == 1) {
			cin >> x >> y >> w;
			DSU_unite(x - 1, y - 1, w);
		} else {
			cin >> x;
			cout << weight[DSU_get(x - 1)]<<'\n';
		}
	}
	
	return 0;
}
