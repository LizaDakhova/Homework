//Ford-Bellman algorithm
#include <iostream>
#include <vector>
#define Inf 1000000000
using namespace std;

//vector uv
struct Edge {
	int s, st, f, ft;
};

int ford_bellman(int n, int k, int a, int b, Edge *edge) {
	vector<int> time_in(n, Inf);
	time_in[a] = 0;
	
	for (;;) {
		bool any = false;
		for (int j = 0; j < k; ++j) {
			Edge e = edge[j];
			if (time_in[e.s] != Inf && time_in[e.s] <= e.st && 
				time_in[e.f] > e.ft) {
				time_in[e.f] = e.ft;
				any = true;
			}
		}		
		if (!any) break;		
	}
	return time_in[b];
}


int main() {
	int n, a, b, k, s, st, f, ft;
	cin >> n >> a >> b >> k;
	
	Edge *edge = new Edge[k];
	
	for (int i = 0; i < k; ++i) {
		cin >> s >> st >> f >> ft;
		edge[i].s = s - 1;
		edge[i].st = st;
		edge[i].f = f - 1;
		edge[i].ft = ft;
	}
	
	cout << ford_bellman(n, k, a - 1, b - 1, edge) << '\n';
	
	delete[] edge;
	
	return 0;
}
