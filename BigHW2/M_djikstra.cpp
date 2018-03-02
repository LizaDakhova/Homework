	//dijkstra algorithm
#include <iostream>
#include <vector>
#include <queue>
#define INF 2000000000
#define MAX_FLOORS 1000000
#define MAX_ELEVATORS_STOPS 100000
using namespace std;

int dijkstra(vector<vector<pair<int, int> > > & graph, int s, int f) {
	int sz = graph.size();
	vector<int> distance(sz, INF);
	distance[s] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > queue;
	queue.push(make_pair(0, s));
	while(!queue.empty()) {
		int u = queue.top().second;
		int wu = queue.top().first;
		queue.pop();
		if (distance[u] < wu)
			continue;
		int u_sz = graph[u].size();
		for (int i = 0; i < u_sz; ++i)
			if (distance[u] != INF) {
				int v = graph[u][i].first, wv = graph[u][i].second;
				if (distance[v] > distance[u] + wv) {
					distance[v] = distance[u] + wv;
					queue.push(make_pair(distance[v], v));
				}
			}
	}
	
	return distance[f];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    unsigned n, up, down, e_in, e_out, l, k, ki, curr_number;
    const unsigned sz = MAX_FLOORS + MAX_ELEVATORS_STOPS;
    cin >> n >> up >> down >> e_in >> e_out >> l;
    curr_number = MAX_FLOORS;
    vector<vector<pair<int, int> > > graph(sz);
    for (int i = 0; i < MAX_FLOORS - 1; ++i) {
        graph[i].push_back(make_pair(i + 1, up));
        graph[MAX_FLOORS - i - 1].push_back(make_pair(MAX_FLOORS - i - 2, down));
    }
    for (int i = 0; i < l; ++i) {
        cin >> k;
        vector<int> elevator_stops(k);
        for (int j = 0; j < k; ++j) {
            cin >> ki;
            elevator_stops[j] = --ki;
        }
        for (int j = 0; j < k; ++j) {
            graph[elevator_stops[j]].push_back(make_pair(curr_number, e_in));
            graph[curr_number].push_back(make_pair(elevator_stops[j], e_out));
            ++curr_number;
        }
        for (int j = curr_number - 1; j > curr_number - k; --j) {
            graph[j].push_back(make_pair(j - 1, 0));
            graph[j - 1].push_back(make_pair(j, 0));
        }
    }
    
    cout << dijkstra(graph, 0, n - 1) << '\n';
	
	return 0;
}
