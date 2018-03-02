//prefix function
#include <iostream>
#include <string>
#include <vector>
#include <stack>

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
	string s0, s;
	cin >> s0 >> s;
	s = s0 + '#' + s;
	vector<int> res;
	prefix_function(s, res);
	int n0 = s0.size(), n = s.size();
	stack<char> st;
	int i = n - 1;
	while (i > n0) {
		if (res[i] == 0) break;
		for (int j = 0; j < res[i]; ++j)
			st.push(s[i - j]);
		st.push(' ');
		i -= res[i];
	}
	if (i == n0) {
		cout << "No\n";
		st.pop();
		while (!st.empty()) {
			char c = st.top();
			cout << c;
			st.pop();
		}
		cout << '\n';
	} else 
		cout << "Yes\n";
	return 0;
}
