#include <iostream>
#include <vector>

bool DFS_if_cycle_and_topsort(std::vector<std::vector<int> > & list_graph, 
	std::vector<char> & visited, std::vector<int> & topsort, int v) {
	visited[v] = 'g';
	int size = list_graph[v].size();
	for (int i = 0; i <  size; ++i) {
		int next_v = list_graph[v][i];
		if (visited[next_v] == 'g') 
			return true;
		if (visited[next_v] == 'w' &&
		DFS_if_cycle_and_topsort(list_graph, visited, topsort, next_v))
			return true;
	}
	visited[v] = 'b';
	topsort.push_back(v);
	return false;
}

bool DFS_check_cycles_and_sort(std::vector<std::vector<int> > & list_graph, 
	std::vector<char> & visited, std::vector<int> & topsort) {
	int size = visited.size();
	for (int i = 0; i < size; ++i)
		if (visited[i] == 'w' && 
			DFS_if_cycle_and_topsort(list_graph, visited, topsort, i))
			return true;
	return false;
}

int main() {
	int n, m, v1, v2;
	std::cin >> n >> m;
	std::vector<std::vector<int> > list_graph(n);
	for (int i = 0; i < m; ++i) {
		std::cin >> v1 >> v2;
		list_graph[v1 - 1].push_back(v2 - 1);
	}
	std::vector<char> visited(n);
	for (int i = 0; i < n; ++i)
		visited[i] = 'w';
	std::vector<int> topsort;
	
	if (DFS_check_cycles_and_sort(list_graph, visited, topsort))
		std::cout << -1;
	else
		for (int i = topsort.size() - 1; i >= 0; --i)
			std::cout << topsort[i] + 1 << ' ';
	std::cout << std::endl;
}
