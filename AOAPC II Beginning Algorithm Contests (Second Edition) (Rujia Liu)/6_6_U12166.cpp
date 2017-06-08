#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<map>
using namespace std;
map<long long, int> m;
int cur;
char s[1 << 20];
void dfs(int dep) {
	if (isdigit(s[cur])) {
		long long t = 0;
		while (isdigit(s[cur]))
			t = t * 10 + s[cur++] - '0';
		m[t << dep]++;
	}
	else {
		cur++;
		dfs(dep + 1);
		cur++;
		dfs(dep + 1);
		cur++;
	}
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		m.clear();
		scanf(" %s", s);
		cur = 0;
		dfs(0);
		int sum = 0, Max = 0;
		for (auto it = m.begin(); it != m.end(); it++) {
			if (it->second > Max)
				Max = it->second;
			sum += it->second;
		}
		cout << sum - Max << endl;
	}
	return 0;
}