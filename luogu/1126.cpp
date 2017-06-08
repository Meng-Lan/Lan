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
typedef pair<P,P> ppp;
#define mp make_pair

//这题坑了一晚上，啊，sad，往前走的时候，check错了，check多了判断vis的，导致第五个点步数多了1

const int maxn = 55;
const char *s = "ESWN";
const int dx[] = { 0,1,0,-1 };
const int dy[] = { 1,0,-1,0 };
int n, m, G[maxn][maxn];
bool vis[maxn][maxn][4];
ppp start;
P over;

bool check(const int &x, const int &y) {
	return x > 0 && x < n&&y > 0 && y < m&&	!G[x][y] &&
		!G[x + 1][y] && !G[x][y + 1] && !G[x + 1][y + 1];
}

int bfs() {
	queue<ppp> q;
	q.push(start);
	vis[start.first.first][start.first.second][start.second.first] = true;
	while (!q.empty()) {
		ppp u = q.front(); q.pop();
		int x = u.first.first, y = u.first.second;
		int dr = u.second.first, d = u.second.second;
		if (u.first == over) return u.second.second;
		for (int i = 1; i <= 3; i++) {
			int xx = x + dx[dr] * i, yy = y + dy[dr] * i;
			if (check(xx, yy)) {
				if (!vis[xx][yy][dr]) {
					vis[xx][yy][dr] = true;
					q.push(mp(mp(xx, yy), mp(dr, d + 1)));
				}
			}
			else
				break;
		}
		for (int i = -1; i <= 1; i++) if (i) {
			int drr = (dr + i + 4) % 4;
			if (check(x, y) && !vis[x][y][drr]) {
				vis[x][y][drr] = true;
				q.push(mp(mp(x, y), mp(drr, d + 1)));
			}
		}
	}
	return -1;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &G[i][j]);
	char c;
	scanf("%d%d%d%d %c", &start.first.first, &start.first.second, &over.first, &over.second,&c);
	for (int i = 0; i < 4; i++)
		if (s[i] == c) {
			start.second.first = i;
			break;
		}
	/*for (int i = 0; i <= n+1; i++) {
		for (int j = 0; j <= m + 1; j++) {
			if (i == start.first.first&&j == start.first.second) {
				putchar('B');
				continue;
			}
			printf("%d", check(i, j));
		}
		putchar('\n');
	}*/
	printf("%d\n", bfs());
	return 0;
}
