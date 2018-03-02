//Ford-Bellman algorithm
#include <iostream>
#include <string.h>
#define Inf 30000
using namespace std;

//vector uv
struct Edge {
	int u, v, w;
};

void ford_bellman(int n, int m, Edge *edge, int *distance) {
	distance[0] = 0;
	for (int i = 0; i < n - 1; ++i) { 
		for (int j = 0; j < m; ++j) {
			Edge e = edge[j];
			if (distance[e.u] < Inf && distance[e.u] + e.w < distance[e.v])
				distance[e.v] = distance[e.u] + e.w;
		}
	}
	for (int i = 0; i < m; ++i) {
		Edge e = edge[i];
		if (distance[e.v] > distance[e.u] + e.w)
			distance[e.v] = Inf;
	}
}


int main() {
	int n, m, u, v, w;
	cin >> n >> m;
	
	Edge *edge = new Edge[m];
	int *distance = new int[n];
	for (int i = 0; i < n; ++i)
		distance[i] = Inf;
	
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		edge[i].u = u - 1;
		edge[i].v = v - 1;
		edge[i].w = w;
	}
	
	ford_bellman(n, m, edge, distance);
	
	for (int i = 0; i < n; ++i)
		cout << distance[i] << ' ';
	
	return 0;
}
