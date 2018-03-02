#include <iostream>
#include <vector>
#include <queue>

int BFS_shortest_way(std::vector<std::vector<char> > &table, int n, int m,
	std::pair<int, int> start) {
	int size = n * m;
	std::vector<std::vector<bool> > visited(size, std::vector<bool>(m, false));
	std::vector<std::vector<int> > distance(size, std::vector<int>(m));
	std::queue<std::pair<int, int> > q;
	
	q.push(start);
	distance[start.first][start.second] = 0;
	
	while (!q.empty()) {
		std::pair<int, int> node = q.front();
		int i, j;
		i = node.first;
		j = node.second;
		visited[i][j] = true;
		q.pop();
		
		if (table[i][j] == 'T')
			return distance[i][j];
			
		if (i - 1 >= 0 && table[i - 1][j] != '#') {
			int next_i = i - 1;
			while (next_i > 0 && table[next_i - 1][j] != '#') --next_i;
			next_i = (i - next_i) / 2 + next_i;
			if (!visited[next_i][j]) {
				//std::cout << "first if: i = " << next_i << ", j = " << j << '\n';
				q.push(std::make_pair(next_i, j));
				distance[next_i][j] = distance[i][j] + 1;
				visited[next_i][j] = true;
			}
		}
		if (i + 1 < n && table[i + 1][j] != '#') {
			int next_i = i + 1;
			while (next_i < n - 1 && table[next_i + 1][j] != '#') ++next_i;
			next_i = next_i - (next_i - i) / 2;
			if (!visited[next_i][j]) {
				//std::cout << "second if: i = " << next_i << ", j = " << j << '\n';
				q.push(std::make_pair(next_i, j));
				distance[next_i][j] = distance[i][j] + 1;
				visited[next_i][j] = true;
			}
		}
		if (j - 1 >= 0 && table[i][j - 1] != '#') {
			int next_j = j - 1;
			while (next_j > 0 && table[i][next_j - 1] != '#') --next_j;
			next_j = (j - next_j) / 2 + next_j;
			if (!visited[i][next_j]) {
				//std::cout << "third if: i = " << i << ", j = " << next_j << '\n';
				q.push(std::make_pair(i, next_j));
				distance[i][next_j] = distance[i][j] + 1;
				visited[i][next_j] = true;
			}
		}
		if (j + 1 < m && table[i][j + 1] != '#') {
			int next_j = j + 1;
			while (next_j < m - 1 && table[i][next_j + 1] != '#') ++next_j;
			next_j = next_j - (next_j - j) / 2;
			if (!visited[i][next_j]) {
				//std::cout << "fourth if: i = " << i << ", j = " << next_j << '\n';
				q.push(std::make_pair(i, next_j));
				distance[i][next_j] = distance[i][j] + 1;
				visited[i][next_j] = true;
			}
		}
	}
	return -1;
}

int main() {
	int n, m, cur_cell;
	std::cin >> n >> m;
	std::pair<int, int> start;
	std::vector<std::vector<char> > table (n);
	char c;
	for (int i = 0; i < n; ++i) {
		table[i].resize(m);
		for (int j = 0; j < m; ++ j) {
			std::cin >> c;
			if (c == 'S')
				start = std::make_pair(i, j);
			table[i][j] = c;
		}
	}
	std::cout << BFS_shortest_way(table, n, m, start) << '\n';
	return 0;
} 
