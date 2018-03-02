//Floyd-Warshall algorithm
#include <iostream>
#include <string.h>
#define Inf 100000000
using namespace std;


void floyd_warshall(int n, int k, int **distance) {
	for (int t = 0; t < k; ++t)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				distance[i][j] = min(distance[i][j], distance[i][t] + distance[t][j]);
}


int main() {
	int n, m, k, s, f, u, v, w;
	cin >> n >> m >> k >> s >> f;
	
	int **distance = new int*[n];
	for (int i = 0; i < n; ++i) {
		distance[i] = new int[n];
		for (int j = 0; j < n; ++j) {
			if (i == j)
				distance[i][j] = 0;
			else
				distance[i][j] = Inf;
		}
	}	
	
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		distance[u - 1][v - 1] = w;
	}
	
	floyd_warshall(n, k, distance);
	
	int result = distance[s - 1][f - 1];
	if (result != Inf)
		cout << result;
	else
		cout << -1;
	
	return 0;
}
