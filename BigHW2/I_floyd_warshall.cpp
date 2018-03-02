//Floyd-Warshall algorithm
#include <iostream>
#define Inf 100000000
using namespace std;


void floyd_warshall(int n, int **distance) {
	for (int t = 0; t < n; ++t)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				distance[i][j] = min(distance[i][j], distance[i][t] + distance[t][j]);
}


int main() {
	int n, s, t, w;
	cin >> n >> s >> t;
	
	int **distance = new int*[n];
	for (int i = 0; i < n; ++i)
		distance[i] = new int[n];	
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			cin >> w;
			if (w != -1)
				distance[i][j] = w;
			else
				distance[i][j] = Inf;
		}
	
	floyd_warshall(n, distance);
	
	int result = distance[s - 1][t - 1];
	if (result != Inf)
		cout << result << '\n';
	else
		cout << -1 << '\n';
	
	for (int i = 0; i < n; ++i)
		delete[] distance[i];
	delete[] distance;
	
	return 0;
}
