#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

class Cgraph
{
public:
	Cgraph(std::vector<std::vector<int> > &g, int n);
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
	int number;
};

Cgraph::Cgraph(std::vector<std::vector<int> > &g, int n) {
	std::copy(g.begin(), g.end(), back_inserter(data));
	int size = g.size();
	time_in.resize(size);
	up.resize(size);
	visit.resize(size);
	timer = 0;       
	number = n;                                   
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
			if (v >= number && up[u] >=  time_in[v] && p != -1)
				junc_points.insert(v - number);
			++children;
		}
	}
	if (v >= number && p == -1 && children > 1)
		junc_points.insert(v - number);
	visit[v] = 2;
}

void Cgraph::find_junc_points() {
	visit.assign(data.size(), 0);
	for (int i = 0; i < data.size(); ++i)
		dfs(i);
}

int main() {
	int n, m, v1, v2, v3;
	std::cin >> n >> m;
	std::vector<std::vector<int> > graph(n + m);
	
	for (int i = 0; i < m; ++i) {
		std::cin >> v1 >> v2 >> v3;
		int pillow = n + i;
		graph[pillow].push_back(v1 - 1);
		graph[pillow].push_back(v2 - 1);
		graph[pillow].push_back(v3 - 1);
		graph[v1 - 1].push_back(pillow);
		graph[v2 - 1].push_back(pillow);
		graph[v3 - 1].push_back(pillow);
	}
	
	Cgraph G(graph, n);
	G.find_junc_points();
	std::cout << G.junc_points.size() << '\n';
	for (std::set<int>::iterator it = G.junc_points.begin(); it != G.junc_points.end(); ++it)
		std::cout << *it + 1 << ' ';
	return 0;
}
