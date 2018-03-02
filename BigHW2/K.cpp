#include <iostream>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
const int INF = 1000000000;
 
typedef vector<vector<int> > matrix;
 
void positive_cycle() {
    cout << "infinitely kind";
    exit(0);
}
 
void find_path(const matrix& dist, const matrix &prev, const matrix& flights_num, vector<int> &ans, int from, int to) {
    vector<int> path;
    if (dist[from][from] > 0)
        positive_cycle();
    for (int cur = to; cur != from && cur != -INF; cur = prev[from][cur]) {
        if (dist[cur][cur] > 0)
            positive_cycle();
        else
            path.push_back(cur);
    }
    path.push_back(from);
    for (int i = path.size() - 1; i > 0; --i) {
        ans.push_back(flights_num[path[i]][path[i - 1]]);
    }
}
 
void floyd(matrix &dist, matrix &prev) {
    size_t n = dist.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (dist[j][k] < dist[j][i] + dist[i][k]) {
                    dist[j][k] = dist[j][i] + dist[i][k];
                    prev[j][k] = prev[i][k];
                }
            }
        }
    }
}
 
vector<int> solve(matrix &dist, matrix &prev, const matrix &flights_num, const vector<int> &route){
    floyd(dist, prev);
    vector<int> ans;
    for (int i = 0; i < route.size() - 1; ++i) {
        find_path(dist, prev, flights_num, ans, route[i], route[i + 1]);
    }
    return ans;
}
 
int main() {
    unsigned int n, m, k;
    int from, to, w;
    cin >> n >> m >> k;
    vector<int> route;
    matrix dist(n, vector<int>(n, -INF));
    matrix prev(n, vector<int>(n, -INF));
    matrix flights_num(n, vector<int>(n));
 
    for (int i = 1; i <= m; ++i) {
        cin >> from >> to >> w;
        --from, --to;
        dist[from][to] = w;
        prev[from][to] = from;
        flights_num[from][to] = i;
    }
 
    for (int i = 0; i < k; ++i) {
        cin >> w;
        route.push_back(--w);
    }
 
    vector<int> ans = solve(dist, prev, flights_num, route);
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << ' ';
 
    return 0;
}

