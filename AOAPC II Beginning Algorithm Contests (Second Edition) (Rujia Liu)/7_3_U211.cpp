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
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair

const int R = 7, C = 8;
const int dx[] = { 1,0 };
const int dy[] = { 0,1 };
int s[R][C], G[R][C], vis[R][C],vc[R*C], ans[R][C],cnt;
P coo[R*C];

bool get_rc() {
	FOR(i, R)
		FOR(j, C)
		if (scanf("%d", &s[i][j]) == EOF) return false;
	return true;
}

void print(int p[][C]) {
	FOR(i, R) {
		FOR(j, C)
			printf("%4d", p[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

bool check(int x, int y) {
	return x >= 0 && x < R&&y >= 0 && y < C;
}

void dfs(int x, int y,int tmo) {
	//printf("%4d", tmo);
	if (y >= C) {
		++x; y = 0;
		if (x >= R) {
			++cnt;
			print(ans);
			return;
		}
	}
	if (ans[x][y]) {
		dfs(x, y + 1, tmo);
	}
	else {
		int u = s[x][y];
		FOR(i, 2) {
			int tx = x + dx[i], ty = y + dy[i];
			if (!check(tx, ty)) continue;
			int v = s[tx][ty];
			if (!ans[tx][ty] && !vc[G[u][v]]) {
				ans[x][y] = ans[tx][ty] = G[u][v]; vc[G[u][v]] = 1;
				dfs(x, y + 1, tmo - 1);
				ans[x][y] = ans[tx][ty] = vc[G[u][v]] = 0;
			}
		}
	}
}

int main() {
	int kase = 0;
	int cot = 0;
	FOR(i, R)
		rep(j, i, R) {
		coo[cot << 1] = mp(i, j);
		coo[cot << 1 | 1] = mp(j, i);
		G[i][j] = G[j][i] = ++cot;
	}
	/*FOR(i, R) {
		FOR(j, R)
			printf("%4d", G[i][j]);
		putchar('\n');
	}
	for (int i = 0; i < R*C; ++i)
		printf("%-4d(%d,%d)\n",i+1, coo[i].first, coo[i].second);*/
	while (get_rc()) {
		if (kase) printf("\n\n\n");
		printf("Layout #%d:\n\n", ++kase);
		print(s);
		printf("Maps resulting from layout #%d are:\n\n", kase);
		cnt = 0; memset(ans, 0, sizeof(ans)); memset(vc, 0, sizeof(vc));
		dfs(0, 0, 28);
		printf("There are %d solution(s) for layout #%d.\n", cnt, kase);
	}
	return 0;
}