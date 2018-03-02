//dijkstra algorithm
#include <iostream>
#include <vector>
#include <queue>
#define INF 2009000999
using namespace std;

void dijkstra(int s, vector<vector<pair<int, int> > > & graph, vector<int> &distance 
	/*, vector<int> &prev*/) {
	distance[s] = 0;
	
	int n = distance.size();
	
	vector<bool> pointed(n, false);
	
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	q.push(make_pair(0, s));
	
	for (int i = 0; !q.empty() && i < n; ++i) {
		int v = q.top().second;
		while(pointed[v]) {
			q.pop();
			v = q.top().second;
		}
		pointed[v] = true;
		q.pop();
			
		int size = graph[v].size();
		for (int j = 0; j < size; ++j) {
			int to = graph[v][j].first;
			int len = graph[v][j].second;
			if (!pointed[to] && distance[to] > (distance[v] + len)) {
				distance[to] = distance[v] + len;
				q.push(make_pair(distance[to], to));
				//prev[to] = v;
			}
		}
	}	
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int num, n, m, v1, v2, w, s;
	cin >> num;
	for (int i = 0; i < num; ++i) {
		cin >> n >> m;
		vector<vector<pair<int, int> > > graph(n);
		
		for (int j = 0; j < m; ++j) {
			cin >> v1 >> v2 >> w;
			graph[v1].push_back(make_pair(v2, w));
			graph[v2].push_back(make_pair(v1, w));
		}
		cin >> s;
		
		vector<int> distance(n, INF);
		//vector<int> prev(n, -1);
		
		dijkstra(s, graph, distance /*, prev*/);
		
		for (int j = 0; j < n; ++j)
			cout << distance[j] << ' ';
		cout << '\n';
	}
	return 0;
}
