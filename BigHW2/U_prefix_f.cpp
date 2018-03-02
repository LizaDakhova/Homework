//prefix function
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int prefix_function(string & s) {
	int n = s.size(), max_z = 0;
	
	vector<int> res(n);
	res[0] = 0;
	
	for (int i = 1; i < n; ++i) {
		int j = res[i - 1];
		while(j > 0 && s[j] != s[i])
			j = res[j - 1];
		if (s[j] == s[i]) ++j;
		res[i] = j;
		if (max_z < j) max_z = j;
	}
	
	return max_z;
}

int main() {
	int n, num0, num1;
	string s1, s2, s_with_0, s_with_1;
	cin >> n >> s1 >> s2;
	s_with_0 = s1 + '#' + s2 + '0' + s2;
	s_with_1 = s1 + '#' + s2 + '1' + s2;
	num0 = prefix_function(s_with_0);
	num1 = prefix_function(s_with_1);
	if (num0 == n - 1 && num1 == n - 1)
		cout << "Random\n";
	else if (num0 == n - 1)
		cout << "No\n";
	else
		cout << "Yes\n";
	return 0;
}
