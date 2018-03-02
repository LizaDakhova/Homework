#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Cgraph {
public:
	Cgraph(std::vector<std::vector<int> > &g1, std::vector<std::vector<int> > &g2);
	std::vector<int> arr;
	std::vector<int> component;
	std::vector<int> visit;
	int color;
	
	void dfs1(int v);
	void dfs2(int v);
	void top_sort();
private:
	std::vector<std::vector<int> > data1;
	std::vector<std::vector<int> > data2;
};

Cgraph::Cgraph(std::vector<std::vector<int> > &g, std::vector<std::vector<int> > &g2) {
	std::copy(g.begin(), g.end(), back_inserter(data1));
	std::copy(g2.begin(), g2.end(), back_inserter(data2));
	component.resize(g.size());
	color = 0;
}

void Cgraph::dfs1(int v) {
	visit[v] = 1;
	for (int i = 0; i < data1[v].size(); i++) {
		int u = data1[v][i];
		if (visit[u] == 0)
			dfs1(u);
	}
	arr.push_back(v);
}

void Cgraph::dfs2(int v)
{
	visit[v] = 1;
	component[v] = color;
	for (int i = 0; i < data2[v].size(); ++i) {
		int u = data2[v][i];
		if (visit[u] == 0)
			dfs2(u);
	}
}

int main()
{
	std::vector<std::vector<int> > graph, graph_invert;
	int n, m, j, k, col;
	std::cin >> n >> m;
	bool tmp = true;
	graph.resize(n);
	graph_invert.resize(n);
	for (int i = 0; i < m; ++i) {
		std::cin >> j >> k;
		graph[j - 1].push_back(k - 1);
		graph_invert[k - 1].push_back(j - 1);
	}
	
	Cgraph G(graph, graph_invert);
	G.visit.assign(n, 0);
	for (int i = 0; i < n; ++i) {
		if (G.visit[i] == 0)
			G.dfs1(i);
	}
	
	G.visit.assign(n, 0);
	G.color = 1;
	for (int i = 0; i < n; ++i) {
		int v = G.arr[n - 1 - i];
		if (G.visit[v] == 0) {
			G.dfs2(v);
			++G.color;
		}
	}
	std::cout << G.color - 1 << '\n';
	for (int i = 0; i < G.component.size(); ++i)
		std::cout << G.component[i] << " ";
	return 0;
}
