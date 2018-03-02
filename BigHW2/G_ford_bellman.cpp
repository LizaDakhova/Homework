//Ford-Bellman algorithm
#include <iostream>
#include <string.h>
#include <vector>
#define Inf 1000000
using namespace std;

//vector uv
struct Edge {
	int u, v, w;
};

int ford_bellman(int n, int m, int k, int s, int f, Edge *edge, int *distance) {
	distance[s] = 0;
	for (int i = 0; i < k; ++i) {
		vector<int> temp_distance(n, Inf);
		for (int j = 0; j < m; ++j) {
			Edge e = edge[j];
			if (distance[e.u] + e.w < distance[e.v])
				temp_distance[e.v] = distance[e.u] + e.w;
		}
		
		for (int j = 0; j < n; ++j)
			if (temp_distance[j] != Inf)
				distance[j] = temp_distance[j];
				
	}
	int result = distance[f];
	if (result != Inf)
		return result;
	else
		return -1;
}


int main() {
	int n, m, k, s, f, u, v, w;
	cin >> n >> m >> k >> s >> f;
	
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
	
	cout << ford_bellman(n, m, k, s - 1, f - 1, edge, distance) << '\n';
	
	delete[] edge;
	delete[] distance;
	
	return 0;
}
