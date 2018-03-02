//algorithm Edmunds_Karp
#include <iostream>
#include <string.h>
#include <queue>
#include <limits.h>

using namespace std;
#define INF 100001

inline bool bfs(/*vector<vector<int> >&*/ int **res_net, /*vector<int> &*/ int *prev, int n, int s, int t) {
	//int n = res_net.size();
	
    vector<bool> visited(n, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    prev[s] = -1;
 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < n; v++)
            if (!visited[v] && res_net[u][v] > 0) {
                prev[v] = u;
                if (v == t)
					return true;
                q.push(v);
                visited[v] = true;
            }
    }
    
    return false;
}

long long edmunds_karp(/*vector<vector<int> > &*/ int **graph, int n, int s, int t) {
    int u, v;
	long long max_flow = 0;
	
	//n = graph.size();
	
    //vector<vector<int> > res_net(graph);
	int **res_net = new int*[n];
	for (int i = 0; i < n; ++i) {
		res_net[i] = new int[n];
		for (int j = 0; j < n; ++j)
			res_net[i][j] = graph[i][j];
	}
	
    //vector<int> prev(n);
    int *prev = new int[n];
 
    while (bfs(res_net, prev, n, s, t)) {
        int path_flow = INT_MAX;
        
        for (v = t; v != s; v = prev[v]) {
            u = prev[v];
            path_flow = min(path_flow, res_net[u][v]);
        }

        for (v = t; v != s; v = prev[v]) {
            u = prev[v];
            res_net[u][v] -= path_flow;
            res_net[v][u] += path_flow;
        }
 
        max_flow += path_flow;
    }
	
	for (int i = 0; i < n; ++i)
		delete[] res_net[i];
	delete[] res_net;
	delete[] prev;
    return max_flow;
}



int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int n, m, u, v, c;
	cin >> n >> m;
	
	int **graph = new int*[n];
	for (int i = 0; i < n; ++i) {
		graph[i] = new int[n];
		for (int j = 0; j < n; ++j)
			graph[i][j] = 0;
	}	
		
	//vector<vector<int> > graph(n, vector<int>(n, 0));

	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		graph[u - 1][v - 1] = c;
	}
	
	cout << edmunds_karp(graph, n,  0, n - 1) << '\n';
	
	for (int i = 0; i < n; ++i)
		delete[] graph[i];
	delete[] graph;
	return 0;
};
