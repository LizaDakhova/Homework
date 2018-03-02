#include <iostream>
#include <vector>
#include <queue>

class Graph {
	int size;
	std::vector<std::vector<int> > graph;
public:
	Graph(int n);
	void add(int v1, int v2);
	int BFS_shortest_way(int start, int finish, std::vector<int> & way);
};

Graph::Graph(int n) {
	size = n;
	graph.resize(size);
}

void Graph::add(int v1, int v2) {
	graph[v1].push_back(v2);
	graph[v2].push_back(v1);
}

int Graph::BFS_shortest_way(int start, int finish, std::vector<int> & way) {
	std::vector<bool> visited(size);
	bool node_found = false;
	for (int i = 0; i < size; ++i)
		visited[i] = false;
	std::vector<int> distance(size);
	std::queue<int> q;
	visited[start] = true;
	q.push(start);
	distance[start] = 0;
	while (!q.empty() && !node_found) {
		int node = q.front();
		q.pop();
		int number_con_nodes = graph[node].size();
		for (int i = 0; i < number_con_nodes; ++i) {
			int con_node = graph[node][i];
			if (con_node == finish) {
				distance[con_node] = distance[node] + 1;
				node_found = true;
			}
			else if (!visited[con_node]) {
				visited[con_node] = true;
				q.push(con_node);
				distance[con_node] = distance[node] + 1;
			}
		}
	}
	if (!node_found)
		return -1;
	else {
		way.push_back(finish);
		int node = finish;
		int dis = distance[finish];
		int temp_dis = dis;
		int index = 0;
		while(temp_dis) {
			int con_node = graph[node][index];
			if (distance[con_node] == temp_dis - 1) {			
				way.push_back(con_node);
				node = con_node;
				--temp_dis;
				index = 0;
			}
			else
				++index;
		}	
		return dis;
	}
}

int main() {
	int n, m, start, finish, v1, v2;
	std::cin >> n >> m;
	std::cin >> start >> finish;
	if (start == finish)
		std::cout << 0 << '\n' << start << ' ';
	else {
		Graph g(n);
		for (int i = 0; i < m; ++i) {
			std::cin >> v1 >> v2;
			g.add(v1 - 1, v2 - 1);
		}
		std::vector<int> way;
		int dis = g.BFS_shortest_way(start - 1, finish - 1, way);
		std::cout << dis << '\n';
		if (dis != -1) {
			for (int i = dis; i >= 0; --i) 
				std::cout << way[i] + 1 << ' ';
		}
	}
	return 0;
} 
