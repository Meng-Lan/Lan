#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<utility>
#include<cstring>
using namespace std;
const int maxn = 1e3 + 5;
const double W = 1000.00;
double Left, Right, x[maxn], y[maxn], r[maxn];
int n,vis[maxn];

bool adj(int i, int j) {
	return sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j])) < r[i] + r[j];
}

bool dfs(int i) {
	if (vis[i]) return false;
	vis[i] = 1;
	if (y[i] - r[i] < 0) return true;
	for (int j = 0; j < n; j++)
		if (adj(i, j) && dfs(j)) return true;
	if (x[i] - r[i] < 0)
		Left = min(Left, y[i] - sqrt((r[i] * r[i] - x[i] * x[i])));
	if (x[i] + r[i] > W)
		Right = min(Right, y[i] - sqrt((r[i] * r[i] - (W - x[i]) *(W - x[i]))));
	return false;
}

int main() {
	while (scanf("%d", &n)==1 && n) {
		memset(vis, 0, sizeof(vis));
		int ok = 1;
		Left = Right = W;
		for (int i = 0; i < n; i++)
			scanf("%lf%lf%lf", x + i, y + i, r + i);
		for (int i = 0; i < n; i++)
			if (!vis[i] && y[i] + r[i] >W&&dfs(i)) {
				ok = 0;
				break;
			}
		if (ok)
			printf("0.00 %.2f %.2f %.2f\n", Left, W, Right);
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}