#include <iostream>
#include <string>
#include <vector>

using namespace std;

void z_function (string &s, vector<int> &res) {
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
	string s;
	cin >> s;
	vector<int> res;
	z_function(s, res);
	int n = s.size();
	cout << n << ' ';
	for (int i = 1; i < n; ++i)
		cout << res[i] <<  ' ';
	return 0;
}
