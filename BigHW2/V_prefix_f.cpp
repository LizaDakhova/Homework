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

int substr_num(string & s) {
	string temp;
	temp = s[0];
	int n = s.size(), num = 1;
	for (int i = 1; i < n; ++i) {
		temp = s[i] + temp;
		num += (i + 1 - prefix_function(temp));
	}
	return num;	
}

int main() {
	string s;
	cin >> s;
	cout << substr_num(s) << '\n';
	return 0;
}
