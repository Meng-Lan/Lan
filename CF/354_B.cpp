#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define mp make_pair
const int maxn = 15;
const int full = 2048;
int n, t;
int G[maxn][maxn];
void dfs(int i, int j, int w) {
	if (w == 0 || i >= n) return;
	if (G[i][j] == full) {
		dfs(i + 1, j, w / 2);
		dfs(i + 1, j + 1, w / 2);
	}
	else {
		G[i][j] += w;
		if (G[i][j] > full) {
			w = G[i][j] - full;
			dfs(i + 1, j, w / 2);
			dfs(i + 1, j + 1, w / 2);
		}
	}
}
int main() {
	scanf("%d%d", &n, &t);
	for (int i = 0; i < t; i++)
		dfs(0, 0, full);
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i; j++)
			if (G[i][j] >= full)
				ans++;
	printf("%d\n", ans);
	return 0;
}