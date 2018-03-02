#include <iostream>
#include <vector>

bool DFS_if_cycle(std::vector<std::vector<int> > & list_graph, 
	std::vector<char> & visited, std::vector<int> & path, int v) {
	visited[v] = 'g';
	path.push_back(v);
	int size = list_graph[v].size();
	for (int i = 0; i <  size; ++i) {
		int next_v = list_graph[v][i];
		if (visited[next_v] == 'g') {
			path.push_back(next_v);
			return true;
		}
		if (visited[next_v] == 'w' &&
		DFS_if_cycle(list_graph, visited, path, next_v))
			return true;
	}
	visited[v] = 'b';
	path.pop_back();
	return false;
}

bool DFS_check_cycles(std::vector<std::vector<int> > & list_graph, 
	std::vector<char> & visited, std::vector<int> & path) {
	int size = visited.size();
	for (int i = 0; i < size; ++i)
		if (visited[i] == 'w' && 
			DFS_if_cycle(list_graph, visited, path, i))
			return true;
	return false;
}

void DFS_show_cycle(std::vector<std::vector<int> > & list_graph, std::vector<char> & visited,
std::vector<int> & path) {
	if (DFS_check_cycles(list_graph, visited, path)) {
		std::cout << "YES\n";
		int size = path.size();
		int i = size - 2;
		int last = path[size - 1];
		while (path[i] != last) --i;
		for (; i < size - 1; ++i)
			std::cout << path[i] + 1 << ' ';
		std::cout << '\n';
	}
	else
		std::cout << "NO\n";
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
	std::vector<int> path;
	
	DFS_show_cycle(list_graph, visited, path);
	
	return 0;
};
