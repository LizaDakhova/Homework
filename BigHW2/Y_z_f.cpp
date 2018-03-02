#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void z_function (vector<int> &s, vector<int> &res) {
	int n = s.size();
	res.resize(n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			res[i] = min(r - i + 1, res[i - l]);
		while (i + res[i] < n && s[res[i]] == s[i + res[i]]) ++res[i];
		if (i + res[i] - 1 > r)
			l = i, r = i + res[i] - 1;
	}
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> s0(n), s(2 * n + 1);
	for (int i = 0; i < n; ++i)
		cin >> s0[i];
	for (int i = 0; i < n; ++i) 
		s[i] = s0[i];
	s[n] = k + 1;
	for (int i = 0; i < n; ++i)
		s[i + n + 1] = s0[n - 1 - i];

	vector<int> res;
	z_function(s, res);
	priority_queue<int, vector<int>, greater<int > > q;
	for (int i = 2 * n; i > n; --i)
		if (res[i] % 2 == 0 && i + res[i] == 2 * n + 1) 
			q.push(n - res[i] / 2 );
	q.push(n);
	int num = 0;
	while(!q.empty()) {
		cout << q.top() << ' ';	
		q.pop();
	}
	return 0;
}
