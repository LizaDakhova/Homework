#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class Graph {
	int size;
    int timer;
    std::vector<std::vector<int> > graph;
    std::vector<std::vector<int> > condensed_graph;
    std::vector<pair<int, int> > bridges;
    std::vector<int> components;
    std::vector<int> time_in;
    std::vector<int> up;
    
public:
    Graph(std::vector<std::vector<int> > &g) {
		timer = 0;
        int n = g.size();
        size = n;
        time_in.resize(n);
        up.resize(n);
        components.resize(n, -1);
        std::copy(g.begin(), g.end(), back_inserter(graph));
        condensed_graph.resize(n);
    }
    
    void dfs(int v, int number) {
        components[v] = number;
        int v_size = graph[v].size();
        for (int i = 0; i <  v_size; ++i) {
			int u = graph[v][i];
            if (components[u] == -1)
                dfs(u, number);
        }
    }
    
    void find_bridges(int v, int parent = -1) {
        time_in[v] = ++timer;
        up[v] = time_in[v];
        int v_size = graph[v].size();
        for (int i = 0; i < v_size; ++i ) {
			int u = graph[v][i];
            if (u == parent)
                continue;
            if (time_in[u])
                up[v] = std::min(up[v], time_in[u]);
            else {
                find_bridges(u, v);
                up[v] = std::min(up[v], up[u]);
            }
        }
        if (parent != -1 && up[v] > time_in[parent])
            bridges.push_back(make_pair(v, parent));
    }
    
    int answer() {
        for (int i = 0; i < size; ++i)
            if (!time_in[i])
                find_bridges(i);

		int bridges_size = bridges.size();
        for (int i = 0; i < bridges_size; ++i) {
            int v1 = bridges[i].first;
            int v2 = bridges[i].second;
            graph[v1].erase(find(graph[v1].begin(), graph[v1].end(), v2));
            graph[v2].erase(find(graph[v2].begin(), graph[v2].end(), v1));
        }
        
        for (int i = 0; i < size; ++i)
            if (components[i] == -1)
                dfs(i, i);
                
        for (int i = 0; i < bridges_size; ++i) {
            int v1 = bridges[i].first;
            int v2 = bridges[i].second;
            condensed_graph[components[v1]].push_back(components[v2]);
            condensed_graph[components[v2]].push_back(components[v1]);
        }
        
        int ans = 0;
        for (int i = 0; i < condensed_graph.size(); ++i)
            if (condensed_graph[i].size() == 1)
                ++ans;
                
        return (ans + 1) / 2;
    }
};

int main() {
	int n, m, v1, v2;
	std::cin >> n >> m;
	std::vector<std::vector<int> > graph(n);
    for (int i = 0; i < m; ++i) {
		cin >> v1 >> v2;
		graph[v1 - 1].push_back(v2 - 1);
		graph[v2 - 1].push_back(v1 - 1);
    }
    Graph gr(graph);
    
    std::cout << gr.answer() << '\n';
    
    return 0;
}
