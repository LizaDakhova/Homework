#include <iostream>
#include <queue>
#include <algorithm>
#define INF 100001

using namespace std;

void edmonds_karp(vector<vector<int> > & edges) {
	int n = edges.size();
	
	vector<vector<int> > flow(n, vector<int>(n, 0));
	vector<vector<int> > res_net (edges);
	vector<bool> visited(n, false);
	vector<int> prev(n, -1);
	queue<int> dfs_queue;
	queue<int> shortest_path;
	
	int u = 0;
	shortest_path.push(u);
	visited[u] = true;
	while(!dfs_queue.empty() && u != n - 1) {
		for (int v = 0; v < n; ++v) {
			if (!visited[v] && res_net[u][v] != INF) {
				dfs_queue.push(v);
				prev[v] = u;
			}
		}
		u = dfs_queue.front();
		dfs_queue.pop();
		visited[u] = true;
	}
		
	
	
}

int main() {
	int n, m, u, v, w;
	cin >> n >> m;
	vector<vector<int> > edges(n, vector<int>(n, INF));
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		edges[--u][--v] = w;
	}
	edmonds_karp(edges);
	return 0;
}
