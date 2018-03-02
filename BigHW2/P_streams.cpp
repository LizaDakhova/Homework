//algorithm Ford-Falkerson
#include <iostream>
#include <string.h>

using namespace std;
#define INF 100001

int size;
int** graph;
bool* visited;
int** flow;

int dfs(int s, int t, int minimum) {
	visited[s] = true;
	
	if (s == t)
		return minimum;
	
	for (int i = 0; i < size; ++i) {
		int flow_capacity = graph[s][i] - flow[s][i];
		if (!visited[i] && flow_capacity > 0) 
			if (int sent = dfs(i, t, min(minimum, flow_capacity))) {
				flow[s][i] += sent;
				flow[i][s] -= sent;
				return sent;
			}
	}
	
	return false;
}

int main() {
	int n, m, u, v, c;
	cin >> n >> m;
	
	//initialization
	size = n;
	graph = new int*[size];
	for (int i = 0; i < size; ++i) {
		graph[i] = new int[size];
		memset(graph[i], 0, size);
	}
	visited = new bool[size];
	memset(visited, false, size);
	flow = new int*[size];
	for (int i = 0; i < size; ++i) {
		flow[i] = new int[size];
		memset(flow[i], 0, size);
	}
	
	//reading
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		graph[u - 1][v - 1] = c;
	}
	
	//algorithm
	int max_flow = 0;
	while (int sent = dfs(0, n - 1, INF)) {
		max_flow += sent;
		memset(visited, 0, size);
	}
	
	cout << max_flow << '\n';
	
	return 0;
};
