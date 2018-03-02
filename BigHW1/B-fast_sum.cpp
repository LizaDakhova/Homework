#include <iostream>
#include <vector>

unsigned a, b;
unsigned cur = 0;
unsigned nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

void get(unsigned &l, unsigned &r) {
    l = nextRand();
    r = nextRand();
    if (l > r) {
        std::swap(l, r);
    }
}

int main() {
    long long m, q;
    unsigned l, r, add, n = 1 << 24, ans = 0;
    unsigned long long mod = 4294967296;
    std::vector<unsigned> vec(n, 0);
    std::cin >> m >> q >> a >> b;
    for (unsigned i = 0; i < m; ++i) {
        add = nextRand();
        get(l, r);
        vec[l] += add;
        vec[r + 1] -= add;
    }
    std::vector<unsigned> sum(n, 0);
    unsigned cur = 0;
    unsigned part_sum = 0;
    for (unsigned i = 0; i < n; ++i) {
        cur += vec[i];
        part_sum += cur;
        sum[i] = part_sum;
    }
    for (unsigned i = 0; i < q; ++i) {
        get(l, r);
        if (l == 0)
            ans = (ans + sum[r] % mod) % mod;
        else
            ans = ((ans + sum[r] % mod - sum[l - 1] % mod) + mod) % mod;
    }
    std::cout << ans << std::endl;
    return 0;
}
