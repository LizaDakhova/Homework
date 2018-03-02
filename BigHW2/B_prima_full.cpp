//The idea is to add extra vertex which is connected with all spies with
//edges that weight is cost to send spy on a mission
#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

using namespace std;

const int INF = INT_MAX - 1;

int prima(vector<vector<int> > & edge) {
	int size = edge.size();
	
	vector<bool> used (size, false);
	vector<double> w_min_edge(size, INF); //unclude weight of min possible edge from vertex i
	vector<int> v_end_edge(size, -1);     //unclude end vertex of edge from vertex i
	w_min_edge[0] = 0;
	
	for (int i = 0; i < size; ++i) {
		int v = -1;
		for (int j = 0; j < size; ++j)
			if (!used[j] && (v == -1 || w_min_edge[j] < w_min_edge[v]))
				v = j;
		used[v] = true;
		for (int v_end = 0; v_end < size; ++v_end)
			if (v != v_end && !used[v_end] && edge[v][v_end] < w_min_edge[v_end]) {
				w_min_edge[v_end] = edge[v][v_end];
				v_end_edge[v_end] = v;
			}
	}
	int result = 0;
	for (int i = 1; i < size; ++i)
		result += w_min_edge[i];
	return result;
}

int main() {
	int n, w;
	cin >> n;
	vector<vector<int > > edge(n + 1, vector<int>(n + 1));
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j) {
			cin >> w;
			edge[i][j] =  w;
		}
	for (int i = 0; i < n; ++i) {
		cin >> w;
		edge[n][i] = w;
		edge[i][n] = w;
	}
	cout << prima(edge) << '\n';
}
