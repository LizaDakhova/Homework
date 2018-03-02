#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <queue>
#define INF numeric_limits<unsigned long long>::max()
#define unll unsigned long long
using namespace std;

void djikstra(vector<vector<pair<unll, unll> > > & graph, vector<unll> & d, 
priority_queue<pair<unll, unll>, vector<pair<unll, unll> >, greater<pair<unll, unll> > > & q) {
	while(!q.empty()) {
		unll u = q.top().second;
		unll wu = q.top().first;
		q.pop();
		if (d[u] < wu)
			continue;
		unll u_sz = graph[u].size();
		for (int i = 0; i < u_sz; ++i)
			if (d[u] != INF) {
				unll v = graph[u][i].first, wv = graph[u][i].second;
				if (d[v] > d[u] + wv) {
					d[v] = d[u] + wv;
					q.push(make_pair(d[v], v));
				}
			}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    unll n, m, k, fire, u, v, w, s, f;
    
    cin >> n >> m >> k;
    
    vector<vector<pair<unll, unll> > > map(n);
    vector<unll> d(n, INF);
    priority_queue<pair<unll, unll>, vector<pair<unll, unll> >, greater<pair<unll, unll> > > q;
    vector<unll> dcave(n, INF);
	priority_queue<pair<unll, unll>, vector<pair<unll, unll> >, greater<pair<unll, unll> > > qcave;
    
    for (int i = 0; i < k; ++i) {
		cin >> fire;
		dcave[fire - 1] = 0;
		qcave.push(make_pair(0, fire - 1)); 
	}
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		map[u - 1].push_back(make_pair(v - 1, w));
		map[v - 1].push_back(make_pair(u - 1, w));
	}
	cin >> s >> f;
	d[s - 1] = 0;
	q.push(make_pair(0, s - 1));
	
	djikstra(map, d, q);
	djikstra(map, dcave, qcave);
	
	if (d[f - 1] >= dcave[f - 1])
		cout << -1 << '\n';
	else
		cout << d[f - 1] << '\n';
	
	return 0;
}
