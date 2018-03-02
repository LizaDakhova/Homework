#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define INF 2e9 + 1

struct Edge {
    int beg, end;
    long long weight;
    bool type;
    int ord;
};

struct Cmp {
    bool operator() (const Edge & fst, const Edge & snd) {
        if (fst.weight != snd.weight) {
            return fst.weight > snd.weight;
        } else if (fst.type != snd.type) {
            return snd.type;
        } else {
            return fst.ord > snd.ord;
        }
    }
};

class DSU {
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int size) {
        parent.resize(size);
        rank.resize(size);
        for (int i = 0; i < size; ++i) {
            make_set(i);
        }
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int fst, int snd) {
        fst = find_set(fst);
        snd = find_set(snd);
        if (fst != snd) {
            if (rank[fst] < rank[snd]) {
                swap(fst, snd);
            }
            parent[snd] = fst;
            if (rank[fst] == rank[snd]) {
                ++rank[fst];
            }
        }
    }
};

class Graph {
    struct Vertex {
        int num;
        long long weight;
    };

    int ver_count;
    vector<vector<Vertex> > graph;
    vector<int> sources;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > queue;
    vector<long long> dist;
    vector<int> prev;

    void Dijkstra() {
        for (int i = 0; i < sources.size(); ++i) {
            dist[sources[i]] = 0;
            prev[sources[i]] = sources[i];
            queue.push({0, sources[i]});
        }
        while(!queue.empty()) {
            int minv = queue.top().second;
            int cur_d = queue.top().first;
            queue.pop();
            if (cur_d > dist[minv]) {
                continue;
            }
            for (auto to: graph[minv]) {
                if (dist[minv] != INF) {
                    if (dist[to.num] > dist[minv] + to.weight) {
                        dist[to.num] = dist[minv] + to.weight;
                        prev[to.num] = prev[minv];
                        queue.push({dist[to.num], to.num});
                    }
                }
            }
        }
    }
public:

    Graph(int ver_count): ver_count(ver_count), graph(ver_count, vector<Vertex>()){
        prev.resize(ver_count, -1);
        dist.resize(ver_count, INF);
    }

    void add_edge(int beg, int end, long long weight) {
        Vertex to, from;
        from.num = beg;
        from.weight = weight;
        to.num = end;
        to.weight = weight;
        graph[beg].push_back(to);
        graph[end].push_back(from);
    }

    void read_graph(int s, int m, vector<Edge> &edges) {
        int beg, end;
        long long w;
        for (int i = 0; i < s; ++i) {
            cin >> beg;
            sources.push_back(beg - 1);
        }
        for (int i = 0; i < m; ++i) {
            cin >> beg >> end >> w;
            add_edge(--beg, --end, w);
            Edge edge;
            edge.beg = beg, edge.end = end, edge.weight = w;
            edge.type = true;
            edges.push_back(edge);
        }
    }

    void get_ans(vector<Edge> &edges, DSU &dsu, vector<int> &order) {
        Dijkstra();
        priority_queue<Edge, vector<Edge>, Cmp> new_edges;
        for (int i = 0; i < edges.size(); ++i) {
            if (edges[i].type) {
                if (prev[edges[i].beg] != prev[edges[i].end]) {
                    edges[i].weight += dist[edges[i].beg] + dist[edges[i].end];
                    new_edges.push(edges[i]);
                }
            } else {
                new_edges.push(edges[i]);
            }
        }
        while (!new_edges.empty()) {
            Edge edge = new_edges.top();
            new_edges.pop();
            if (edge.type) {
                dsu.union_sets(prev[edge.beg], prev[edge.end]);
            } else {
                if (dsu.find_set(prev[edge.beg]) == dsu.find_set(prev[edge.end])) {
                    order[edge.ord] = 1;
                } else {
                    order[edge.ord] = 0;
                }
            }
        }
        for (int i = 0; i < order.size(); ++i) {
            if (order[i]) {
                cout << "TAK\n";
            } else {
                cout << "NIE\n";
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, s, m, q, beg, end;
    long long w;
    vector<Edge> edges;
    cin >> n >> s >> m;
    Graph gr(n);
    DSU dsu(n);
    gr.read_graph(s, m, edges);
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> beg >> end >> w;
        Edge edge;
        edge.beg = --beg, edge.end = --end, edge.weight = w, edge.type = false;
        edge.ord = i;
        edges.push_back(edge);
    }
    vector<int> order(q);
    gr.get_ans(edges, dsu, order);
}
