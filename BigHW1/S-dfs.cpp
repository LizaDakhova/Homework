#include <iostream>
#include <vector>

void DFS_if_cycle(std::vector<std::vector<int> > & list_graph, 
	std::vector<char> & visited, int v, int & answer) {
	visited[v] = 'g';
	int size = list_graph[v].size();
	for (int i = 0; i <  size; ++i) {
		int next_v = list_graph[v][i];
		if (visited[next_v] == 'g') {
			answer++;
		}
		if (visited[next_v] == 'w')
			DFS_if_cycle(list_graph, visited, next_v, answer);
	}
	visited[v] = 'b';
}

int DFS_check_cycles(std::vector<std::vector<int> > & list_graph, 
	std::vector<char> & visited) {
	int answer = 0;
	int size = visited.size();
	for (int i = 0; i < size; ++i)
		if (visited[i] == 'w') 
			DFS_if_cycle(list_graph, visited, i, answer);
	return answer;
}

int main() {
	int n, v;
	std::cin >> n;
	std::vector<std::vector<int> > list_graph(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> v;
		list_graph[v - 1].push_back(i);
	}
	std::vector<char> visited(n);
	for (int i = 0; i < n; ++i)
		visited[i] = 'w';
	
	std::cout << DFS_check_cycles(list_graph, visited) << std::endl;
	
	return 0;
};
