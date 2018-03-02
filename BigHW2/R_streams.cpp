#include <iostream>
#include <vector>
#include <queue>
 
#define INF 2e9
 
using namespace std;
 
class Graph {
    int ver_count;
    int source;
    int sink;
    vector<int> prev;
    vector<int> cur_path_cap;
    vector<vector<int> > capacities;
    vector<vector<int> > cur_flow;
    vector<vector<int> > graph;
 
    int bfs() {
        queue<int> order;
        prev.assign(ver_count, -1);
        cur_path_cap.assign(ver_count, 0);
        order.push(source);
        prev[source] = -2;
        cur_path_cap[source] = INF;
        while(!order.empty()) {
            int curr = order.front();
            order.pop();
            for (auto to: graph[curr]) {
                if (prev[to] == -1) {
                    if (capacities[curr][to] - cur_flow[curr][to] > 0) {
                        prev[to] = curr;
                        cur_path_cap[to] = min(cur_path_cap[curr],
                                               capacities[curr][to] - cur_flow[curr][to]);
                        if (to == sink) {
                            return cur_path_cap[to];
                        }
                        order.push(to);
                    }
                }
            }
        }
        return 0;
    }
 
public:
    Graph(int ver_count): ver_count(ver_count), cur_flow(ver_count, vector<int>(ver_count, 0)),
                          cur_path_cap(ver_count, 0), graph(ver_count, vector<int>()),
                          capacities(ver_count, vector<int>(ver_count)){
        prev.resize(ver_count, -1);
        source = ver_count - 2;
        sink = ver_count - 1;
    }
 
    void add_edge(int beg, int end, int cap) {
        graph[beg].push_back(end);
        graph[end].push_back(beg);
        capacities[beg][end] = cap;
    }
 
    long long Edmonds_Karp() {
        long long max_flow = 0;
        while (true) {
            int flow = bfs();
            if (!flow) {
                break;
            }
            max_flow += flow;
            int curr = sink;
            while (curr != source) {
                int pr = prev[curr];
                cur_flow[pr][curr] += flow;
                cur_flow[curr][pr] -= flow;
                curr = pr;
            }
        }
        return max_flow;
    }
 
};
 
int eval_char(char in) {
    switch(in) {
        case '.':
            return 0;
        case 'H':
            return 1;
        case 'O':
            return 2;
        case 'N':
            return 3;
        case 'C':
            return 4;
    }
}
 
int read_graph(int n, int m, Graph& gr) {
    char c;
    int total = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c;
            int cur = eval_char(c);
            total += cur;
            if ((i + j) % 2) {
                gr.add_edge(n * m, m * i + j, cur);
            } else {
                gr.add_edge(m * i + j, n * m + 1, cur);
            }
            if (i != n - 1) {
                gr.add_edge(m * i + j, m * (i + 1) + j, 1);
            }
            if (i != 0) {
                gr.add_edge(m * i + j, m * (i - 1) + j, 1);
            }
            if (j != 0) {
                gr.add_edge(m * i + j, m * i + j - 1, 1);
            }
            if (j != m - 1) {
                gr.add_edge(m * i + j, m * i + j + 1, 1);
            }
        }
    }
    return total;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    cin >> n >> m;
    Graph gr(n * m + 2);
    int total = read_graph(n, m, gr);
    if (total != 0 && gr.Edmonds_Karp() * 2 == total) {
        cout << "Valid";
    } else {
        cout << "Invalid";
    }
    return 0;
}
