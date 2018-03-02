//Ford-Bellman algorithm
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#define Inf 1000000000
#define Inf0 100000
using namespace std;

//vector uv
struct Edge {
	int u, v, w;
};

bool ford_bellman(int n, int m, Edge *edge, int *distance, int *parent,
	vector<int> & path) {
	distance[0] = 0;
	int x; //vertex where we can find negative circle
	for (int i = 0; i < n; ++i) { 
		x = -Inf;
		for (int j = 0; j < m; ++j) {
			Edge e = edge[j];
			if (distance[e.u] + e.w < distance[e.v]) {
				distance[e.v] = max(distance[e.u] + e.w, -Inf);
				parent[e.v] = e.u;
				x = e.v;
			}	
		}
	}
	if (x == -Inf)
		return true;
	else {
		int y = x;
		for (int i = 0; i < n; ++i)
			y = parent[y];
		
		for (int z = y; ; z = parent[z]) {
			path.push_back(z);
			if (z == y && path.size() > 1) break;
		}
		reverse(path.begin(), path.end());
		
		return false;
	}
}


int main() {
	int n, w;
	cin >> n;
	
	Edge *edge = new Edge[n * n];
	int *distance = new int[n];
	for (int i = 0; i < n; ++i)
		distance[i] = Inf;
	int *parent = new int[n];
	for (int i = 0; i < n; ++i) 
		parent[i] = -1;
	vector<int> path;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> w;
			if (w != 0 && w != Inf0) {
				edge[i * n + j].u = i;
				edge[i * n + j].v = j;
				edge[i * n + j].w = w;
			}
		}
	}
	
	if (ford_bellman(n, n * n, edge, distance, parent, path))
		cout << "NO\n";
	else {
		cout << "YES\n";
		int size = path.size();
		cout << size << '\n';
		for (int i = 0; i < size; ++i)
			cout << path[i] + 1 << ' ';
		cout << '\n';
	}	
	
	return 0;
}
