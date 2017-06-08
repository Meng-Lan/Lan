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
typedef pair<P, int> pi;
#define mp make_pair
#define FOR(i,len) for(int i=0;i<(len);++i)

const int maxn = 22;
const int maxnn = maxn*maxn;
const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,-1,0,1 };
const char dr[] = "eswn";
const int d[] = { 0,3,1,2 };
const int ans_vis[] = { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0 };
int n, k, ans[maxn], cnt, G[maxnn][maxnn];
int *vis = &G[maxnn / 2][maxnn / 2];
map<int, vector<int>> X, Y;

bool check(const int &x, const int &tx, const int &y, const int &ty) {
	if (x == tx) {
		int low = min(y, ty), upp = max(y, ty);
		for (auto t : X[x])
			if (t >= low&&t <= upp) return false;
	}
	else if (y == ty) {
		int low = min(x, tx), upp = max(x, tx);
		for (auto t : Y[y])
			if (t >= low&&t <= upp) return false;
	}
	else return false;
	return true;
}

void dfs(int x, int y, int dir, int idx) {
	if (idx > n) return;
	if (x == 0 && y == 0 && idx == n) {
		for (int i = 0; i < n; i++)
			putchar(dr[ans[i]]);
		if (n) putchar('\n');
		++cnt;
		return;
	}
	for (int i = 1; i >= -1; --i) if (i) {
		int j = (dir <= 1) ? -i : i;
		int tdir = (dir + j + 4) % 4; ans[idx] = tdir;
		int tx = x + dx[tdir] * (idx + 1), ty = y + dy[tdir] * (idx + 1);
		if (check(x, tx, y, ty) && !vis[tx*maxnn + ty]) {
			vis[tx*maxnn + ty] = 1;
			dfs(tx, ty, tdir, idx + 1);
			vis[tx*maxnn + ty] = 0;
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int x, y;
		cnt = 0; memset(ans, 0, sizeof(ans));
		X.clear(); Y.clear(); memset(G, 0, sizeof(G));
		scanf("%d%d", &n, &k);
		FOR(i, k) {
			scanf("%d%d", &x, &y);
			X[x].push_back(y);
			Y[y].push_back(x);
		}
		if (ans_vis[n])
			for (int i = 0; i < 4; i++) {
				x = dx[d[i]]; y = dy[d[i]]; ans[0] = d[i]; vis[x*maxnn + y] = 1;
				if (check(0, x, 0, y)) dfs(x, y, d[i], 1); vis[x*maxnn + y] = 0;
			}
		printf("Found %d golygon(s).\n\n", cnt);
	}
	return 0;
}