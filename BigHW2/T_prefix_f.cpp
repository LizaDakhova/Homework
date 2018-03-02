//prefix function
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int prefix_function(string & s, vector<int> &res) {
	int n = s.size(), x;
	
	res.resize(n);
	res[0] = 0;
	
	for (int i = 1; i < n; ++i) {
		int j = res[i - 1];
		while(j > 0 && s[j] != s[i])
			j = res[j - 1];
		if (s[j] == s[i]) ++j;
		res[i] = j;
	}
}

int main() {
	string s, s0;
	cin >> s >> s0;
	s = s0 + '#' + s;
	vector<int> res;
	prefix_function(s, res);
	int n = s.size(), n0 = s0.size();
	for (int i = 2 * n0; i < n; ++i)
		if (res[i] == n0)
			cout << i - 2 * n0 << ' ';
	return 0;
}
