#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1e3 + 5;
int v, e, t;
int degree[maxn],vis[maxn][maxn];
int main() {
	int kase = 0;
	while (scanf("%d%d%d", &v, &e, &t) && v) {
		int u, v;
		memset(degree, 0, sizeof(degree));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < e; i++) {
			scanf("%d%d", &u, &v);
			if (!vis[u][v]) {
				degree[u]++;
				degree[v]++;
				vis[u][v] = vis[v][u] = true;
			}
		}
		int new_degree = 0, sum = 0;
		for (auto temp : degree) {
			if (temp & 1)
				new_degree++;
			sum += temp;
		}
		if (new_degree >= 2)
			printf("Case %d: %d\n", ++kase, ((sum + new_degree - 2) / 2)*t);
		else
			printf("Case %d: %d\n", ++kase, (sum / 2)*t);
	}
	return 0;
}