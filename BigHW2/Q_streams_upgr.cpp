#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1e10
#define MAX 505

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
    int exists[MAX][MAX];

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
        source = 0;
        sink = ver_count - 1;
    }

    void add_edge(int beg, int end, int cap) {
        if (!exists[beg][end]) {
            graph[beg].push_back(end);
            graph[end].push_back(beg);
            exists[beg][end] = 1;
        }
        capacities[beg][end] += cap;
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

void read_graph(int m, Graph& gr) {
    for (int i = 0; i < m; ++i) {
        int fst, snd, cap;
        cin >> fst >> snd >> cap;
        gr.add_edge(--fst, --snd, cap);
    }
}

void print_ans(Graph& gr) {
    cout << gr.Edmonds_Karp();
}

int main() {
    int n, m;
    cin >> n >> m;
    Graph gr(n);
    read_graph(m, gr);
    print_ans(gr);
    return 0;
}
