#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
using namespace std;
#define FOR(i) for(int i=0;i<(maxn);i++)
const int maxn = 30;
int n, G[maxn][maxn], vis[maxn][maxn], in[maxn], out[maxn];
char s[1005];

void dfs(int u) {
	for (int v = 0; v < maxn; v++)
		if (G[u][v] && !vis[u][v]) {
			vis[u][v] = 1;
			dfs(v);
		}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		string temp;
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			int len = strlen(s);
			//cout << len <<"-----"<< endl;
			G[s[0] - 'a'][s[len - 1] - 'a'] = 1;
			in[s[0] - 'a']++;
			out[s[len-1] - 'a']++;
		}
		int degree = 0;
		vector<int> in_degree, out_degree;
		FOR(i) {
			if (in[i] != out[i])
				degree++;
			if (in[i] - out[i] == 1)
				in_degree.push_back(i);
			if (out[i] - in[i] == 1)
				out_degree.push_back(i);
		}
		if (degree == 2&& in_degree.size() == 1 && out_degree.size() == 1 || degree == 0) {
			if (degree == 2)
				dfs(in_degree[0]);
			else
				FOR(i)
				if (in[i] > 0) {
					dfs(i);
					break;
				}
			bool off = true;
			FOR(i)
				FOR(j) {
				if (G[i][j] != vis[i][j]) {
					//cout << i << "  " << j << endl;
					off = false;
				}
			}
			if (off)
				printf("Ordering is possible.\n");
			else
				printf("The door cannot be opened.\n");
		}
		else
			printf("The door cannot be opened.\n");
	}
	return 0;
}