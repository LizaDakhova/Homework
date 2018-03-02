#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Info {
	char operates; //true = add, false = cut
	pair<int, int> edge; // v, u
};
class G {
public:
	vector<int> parent;
	vector<bool> answers;
	vector<Info> data;
	int Find_set(int n);
	int Union(int x, int y);
	G(int n, int m, int k) {
		parent.resize(n + 1);
		answers.resize(k + 1);
		data.resize(k + 1);
	}
};

int G::Find_set(int n) { 
	if (n == parent[n]) 
		return n;
	return parent[n] = Find_set(parent[n]);
}

int G::Union(int x, int y) {
	int x1 = Find_set(x);
	int y1 = Find_set(y);
	
	parent[x1] = y1;
	return (x1 == y1);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m, k, v, u;
	cin >> n >> m >> k;
	G g(n, m, k);
	Info s;
	string c;
	for (int i = 0; i < m; i++)
		cin >> v >> u;
	for (int i = 0; i < k; i++) {
		cin >> c >> v >> u;
		if (c[0] == 'a')
			s.operates = true;
		else 
			s.operates = false;
		s.edge.first = v;
		s.edge.second = u;
		g.data[i] = s;
	}
	for (int i = 1; i <= n; i++)
		g.parent[i] = i;															
	for (int i = k - 1; i >= 0; i--) {
		if (g.data[i].operates)  
			g.answers[i] = (g.Find_set(g.data[i].edge.first) == g.Find_set(g.data[i].edge.second));
		else 
			g.Union(g.data[i].edge.first, g.data[i].edge.second);
	}
	for (int i = 0; i < k; i++)
		if (g.data[i].operates)
			if (g.answers[i])
				cout << "YES" << '\n';
			else 
				cout << "NO" << '\n'; 
	return 0;
}
