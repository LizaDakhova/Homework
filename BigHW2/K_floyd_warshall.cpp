//Floyd-Warshall algorithm
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1000000000
using namespace std;


void floyd_warshall(vector<vector<int> > & distance, vector<vector<int> > & prev) {
	int n = distance.size();
	for (int t = 0; t < n; ++t)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) 
				if (distance[i][j] < distance[i][t] + distance[t][j]) {
					distance[i][j] = distance[i][t] + distance[t][j];
					prev[i][j] = prev[t][j];
				}
}

bool find_path(int s, int f, vector<int> & path,
	vector<vector<int> > & distance, vector<vector<int> > &prev) {
	if (distance[s][s] > 0)
		return false;
	for (int cur = f; cur != s && cur != -INF; cur = prev[s][cur]) {
		if (distance[cur][cur] > 0)
			return false;
		path.push_back(cur);
	}
	reverse(path.begin(), path.end());
	return true;
}

int main() {
	int n, m, k, b, e, w, c;
	cin >> n >> m >> k;
	
	vector<vector<int> > distance(n, vector<int>(n, -INF));
	//for (int i = 0; i < n; ++i) distance[i][i] = 0;
	vector<vector<int> > prev(n, vector<int> (n, -INF));
	vector<vector<int> > flight(n, vector<int>(n));
	int *city = new int[k];
	
	for (int i = 0; i < m; ++i) {
		cin >> b >> e >> w;
		distance[b - 1][e - 1] = w;
		prev[b - 1][e - 1] = b - 1;
		flight[b - 1][e - 1] = i + 1;
	}
	
	for (int i = 0; i < k; ++i) {
		cin >> c;
		city[i] = c - 1;
	}
	
	floyd_warshall(distance, prev);
	bool result = true;	
	vector<int> answer;
	
	if (result) {
		for (int i = 0; i < k - 1; ++i) {
			int s = city[i], f = city[i + 1];
			vector<int> path;
			if (find_path(s, f, path, distance, prev)) {
				int c1 = s, c2, size = path.size();
				for (int j = 0; j < size; ++j) {
					c2 = path[j];
					answer.push_back(flight[c1][c2]);
					c1 = c2;
				}
				//answer.push_back(flight[c2][f]);
			}else {
				result = false;
				break;
			}
		}
	}
	if (result) {
		int size = answer.size();
		cout << size << '\n';
		for (int i = 0; i < size; ++i)
			cout << answer[i] << ' ';
		cout << '\n';
	} else 
		cout << "infinitely kind\n";
	
	delete[] city;
	
	return 0;
}
