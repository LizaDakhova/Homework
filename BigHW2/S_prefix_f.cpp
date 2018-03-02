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
	string s;
	cin >> s;
	vector<int> res;
	prefix_function(s, res);
	int n = s.size();
	for (int i = 0; i < n; ++i)
		cout << res[i] << ' ';
	return 0;
}
