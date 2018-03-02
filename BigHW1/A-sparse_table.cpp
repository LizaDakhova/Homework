#include <iostream>
#include <vector>
#include <algorithm>

class SparseTable {
	std::vector<std::vector<int> > sparse_table;
    std::vector<int> deg;
public:
    
    SparseTable(const std::vector<int> &v) {
        sparse_table.push_back(v);
        deg.resize(v.size() + 1);
        deg[1] = 0;
        for (int i = 2; i <= v.size(); ++i)
            deg[i] = deg[i >> 1] + 1;
        for (int i = 1; (1 << i) <= v.size(); ++i) {
            sparse_table.push_back(std::vector<int>());
            for (int j = 0; j + (1 << i) <= v.size(); ++j)
                sparse_table[i].push_back(std::min(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]));
        }
    }
    
    int get(int l, int r) {
        if (l > r) {
            int tmp = r;
            r = l;
            l = tmp;
        }
        int k = deg[r - l + 1]; //2^k <= r - l + 1
        return std::min(sparse_table[k][l], sparse_table[k][r - (1 << k) + 1]);
    }
};

int main() {
    int n, m, a, u, v, ans;
    std::cin >> n >> m >> a >> u >> v;
    std::vector<int> vec;
    vec.push_back(a);
    for (int i = 1; i < n; ++i) {
        vec.push_back((23 * vec[i - 1] + 21563) % 16714589);
    }
    
    SparseTable st(vec);
    for (int i = 0; i < m - 1; ++i) {
        ans = st.get(u - 1, v - 1);
        u = (17 * u + 751 + ans + 2 * (i + 1)) % n + 1;
        v = (13 * v + 593 + ans + 5 * (i + 1)) % n + 1;
    }
    ans = st.get(u - 1, v - 1);
    std::cout << u << ' ' << v << ' ' << ans << std::endl;
    return 0;
}
