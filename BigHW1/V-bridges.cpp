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
	std::vector<std::pair<int, int> > bridge;
	int timer;
	int counter;
	
	void dfs(int, int);
	void find_bridges();

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
	int size = data[v].size();
	for (int i = 0; i < size; ++i) {
		int u = data[v][i];
		if (visit[u] == 1 && u != p)
			up[v] = std::min(up[v], time_in[u]);
		else if (visit[u] == 0) {
			dfs(u, v);
			up[v] = std::min(up[v], up[u]);
			if (up[u] > time_in[v])
				bridge.push_back(std::make_pair(v, u));
		}
	}
	visit[v] = 2;
	//++timer;
}

void Cgraph::find_bridges() {
	visit.assign(data.size(), 0);
	for (int i = 0; i < data.size(); ++i)
		dfs(i);
}

int main() {
	std::vector<std::vector<int> > graph;
	std::map<std::pair<int, int>,int> edges0;
	std::set<std::pair<int, int> > multiedges;
	std::set<int> edges;
	int n, m, i, j;
	std::cin >> n >> m;
	graph.resize(n);
	std::pair<int, int> a;
	std::pair<int, int> b;
	
	for (int k = 0; k < m; ++k) {
		std::cin >> i >> j;
		a = std::make_pair(j - 1, i - 1);
		b = std::make_pair(i - 1, j - 1);
		graph[j - 1].push_back(i - 1);
		graph[i - 1].push_back(j - 1);
		
		if (edges0[a] != 0 && edges0[b] != 0) {
			multiedges.insert(a);
			multiedges.insert(b);
		}
		edges0[a] = k + 1;
		edges0[b] = k + 1;	
	}
	
	Cgraph G(graph);
	G.find_bridges();
	
	for (int i = 0; i < G.bridge.size(); ++i)
		if (multiedges.find(G.bridge[i]) == multiedges.end())
			edges.insert(edges0[G.bridge[i]]);
	std::cout << edges.size() << '\n';
	
	for (std::set<int>::iterator it = edges.begin(); it != edges.end(); ++it)
		std::cout << *it << '\n';
		
	return 0;
}
