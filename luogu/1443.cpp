#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
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
const int maxn = 205;
const int dx[] = { 2,1,-1,-2,-2,-1,1,2 };
const int dy[] = { 1,2,2,1,-1,-2,-2,-1 };
int n, m, sx, sy, G[maxn][maxn];

bool check(int x, int y) {
	return x > 0 && x <= n&&y > 0 && y <= m;
}
void bfs() {
	memset(G, -1, sizeof(G));
	queue<P> q;
	q.push(mp(sx, sy));
	G[sx][sy] = 0;
	while (!q.empty()) {
		P lan = q.front(); q.pop();
		for (int i = 0; i < 8; i++) {
			int x = lan.first + dx[i];
			int y = lan.second + dy[i];
			if (G[x][y] == -1&&check(x,y)) {
				G[x][y] = G[lan.first][lan.second] + 1;
				q.push(mp(x, y));
			}
		}
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &sx, &sy);
	bfs();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			printf("%-5d", G[i][j]);
		putchar('\n');
	}
	return 0;
}