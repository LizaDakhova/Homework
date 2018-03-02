#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

using namespace std;

const int INF = INT_MAX - 1;

double Prima_roads(vector<pair<int, int> > & vertexes) {
	int size = vertexes.size();
	vector<vector<double> > w_edges(size, vector<double>(size));
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			int xi, yi, xj, yj;
			xi = vertexes[i].first;
			yi = vertexes[i].second;
			xj = vertexes[j].first;
			yj = vertexes[j].second;
			w_edges[i][j] = sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj));
		} 
	}
	
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
			if (v != v_end && !used[v_end] && w_edges[v][v_end] < w_min_edge[v_end]) {
				w_min_edge[v_end] = w_edges[v][v_end];
				v_end_edge[v_end] = v;
			}
	}
	
	double result = 0;
	for (int i = 1; i < size; ++i)
		result += w_min_edge[i];
	return result;
}

int main() {
	int n, x, y;
	cin >> n;
	vector<pair<int, int> > vertexes;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y;
		vertexes.push_back(make_pair(x, y));
	}
	cout << fixed;
	cout.precision(6);
	cout << Prima_roads(vertexes) << '\n';
}
