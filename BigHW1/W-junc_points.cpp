#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

class Cgraph
{
public:
	Cgraph(std::vector<std::vector<int> > &g);
	std::vector<int> time_in;
	std::vector<int> up;
	std::vector<int> visit;
	std::set<int> junc_points;
	int timer;
	int counter;
	
	void dfs(int, int);
	void find_junc_points();

private:
	std::vector<std::vector<int> > data;
};

Cgraph::Cgraph(std::vector<std::vector<int> > &g) {
	std::copy(g.begin(), g.end(), back_inserter(data));
	int size = g.size();
	time_in.resize(size);
	up.resize(size);
	visit.resize(size);
	timer = 0;
	counter = 0;                                             
}

void Cgraph::dfs(int v, int p = -1) {
	visit[v] = 1;
	++timer;
	time_in[v] = up[v] = timer;
	int children = 0;
	int size = data[v].size();
	for (int i = 0; i < size; ++i) {
		int u = data[v][i];
		if (u == p)
			continue;
		if (visit[u] == 1)
			up[v] = std::min(up[v], time_in[u]);
		else if (visit[u] == 0) {
			dfs(u, v);
			up[v] = std::min(up[v], up[u]);
			if (up[u] >=  time_in[v] && p != -1)
				junc_points.insert(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		junc_points.insert(v);
	visit[v] = 2;
}

void Cgraph::find_junc_points() {
	visit.assign(data.size(), 0);
	for (int i = 0; i < data.size(); ++i)
		dfs(i);
}

int main() {
	std::vector<std::vector<int> > graph;
	std::set<std::pair<int, int> > edges;
	int n, m, i, j, k;
	std::cin >> n >> m;
	graph.resize(n);
	std::pair<int, int> a;
	std::pair<int, int> b;
	
	for (int k = 0; k < m; k++) {
		std::cin >> i >> j;
		a = std::make_pair(j - 1, i - 1);
		b = std::make_pair(i - 1, j - 1);
		if (edges.find(a) == edges.end()) {
			graph[j - 1].push_back(i - 1);
			graph[i - 1].push_back(j - 1);
			edges.insert(a);
			edges.insert(b);
		}
	}
	Cgraph G(graph);
	G.find_junc_points();
	std::cout << G.junc_points.size() << '\n';
	for (std::set<int>::iterator it = G.junc_points.begin(); it != G.junc_points.end(); ++it)
		std::cout << *it + 1 << '\n';
	return 0;
}
