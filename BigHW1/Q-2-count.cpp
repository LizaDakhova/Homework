#include <iostream>
#include <vector>
#include <queue>
 
inline char invert(char c) {
    return c == 'r' ? 'b' : 'r';
}
 
void dfs(std::vector<std::vector<int> > & list_graph, std::vector<char> & color,
int v, char c, bool & result) {
    color[v] = c;
 
	int size = list_graph[v].size();
    for (int i = 0; i < size; ++i) {
		int next_v = list_graph[v][i];
        if (color[next_v] == 'w')
            dfs(list_graph, color, next_v, invert(c), result);
        else if (color[next_v] == c)
            result = false;
    }
}
 
int main() {
    int n, m, v1, v2;
	std::cin >> n >> m;
	std::vector<std::vector<int> > list_graph(n);
	for (int i = 0; i < m; ++i) {
		std::cin >> v1 >> v2;
		if (v1 != v2) {
			list_graph[v1 - 1].push_back(v2 - 1);
			list_graph[v2 - 1].push_back(v1 - 1);
		}
		else
			list_graph[v1 - 1].push_back(v1 - 1);
	}
	std::vector<char> color(n, 'w');
	//std::vector<char> number_of_part(n);
	
	bool flag = true;
    for (int i = 0; i < n; i++)
        if (color[i] == 'w') {
			dfs(list_graph, color, i, 'r', flag);
			if (!flag) {
				std::cout << "NO\n";
				break;
			}
		}
    if (flag) std::cout << "YES\n";
    return 0;
}

