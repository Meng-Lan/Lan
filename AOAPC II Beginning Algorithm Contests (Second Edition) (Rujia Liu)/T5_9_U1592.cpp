#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<string>
#include<utility>
#include<cstring>
using namespace std;
const int M = 15;
const int N = 10005;
typedef pair<int, int> P;
map<string,int> idcache;
int cnt, n, m, db[N][M];
string getstr(char * s) {
	int c;
	while ((c = getchar()) == '\n' || c == ' ')
		;
	s[0] = c;
	for (int i = 1; (c = getchar()) != ',' && c != '\n' && c != EOF; i++)
		s[i] = c;
	string str = s;
	return str;
}
int ID(const string &s) {
	if (!idcache.count(s))
		idcache[s]=++cnt;
	return idcache[s];
}
void find() {
	for (int i = 0; i < m; i++)
		for (int j = i + 1; j < m; j++) {
			map<P, int> ans;
			for (int k = 0; k < n; k++) {
				P p = make_pair(db[k][i], db[k][j]);
				if (ans.count(p)) {
					cout << "NO\n";
					cout << ans[p] + 1 << " " << k+1 << endl;
					cout << i+1 << " " << j+1 << endl;
					return;
				}
				ans[p] = k;
			}
		}
	cout << "YES\n";
}
int main() {
	while (cin >> n >> m) {
		char str[105];
		idcache.clear();
		cnt = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				memset(str, 0, sizeof(str));
				db[i][j] = ID(getstr(str));
			}
		find();
	}
	return 0;
}