#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<utility>
#include<queue>
using namespace std;
const int maxn = 25;
const int INF = 10000;
int vis[maxn][maxn], v[maxn][maxn], map[maxn][maxn];
int m, n, k;

struct Lan {
	int x, y, k, d;
	Lan(int x, int y, int k, int d) :x(x), y(y), k(k), d(d) {}
};

const int dx[] = { -1,0,1,0 };
const int dy[] = { 0,-1,0,1 };

bool inside(const int &x,const int &y) {
	return x >= 0 && x < m&&y >= 0 && y < n;
}
bool bfs() {
	memset(vis, 0, sizeof(vis));
	memset(v, 0, sizeof(v));
	queue<Lan> q;
	q.push(Lan(0, 0, k, 0));
	while (!q.empty()) {
		Lan t = q.front();
		q.pop();
		if (t.x == m - 1 && t.y == n - 1) {
			printf("%d\n", t.d);
			return true;
		}
		for (int i = 0; i < 4; i++) {
			int x = t.x + dx[i];
			int y = t.y + dy[i];
			if (inside(x, y) && map[x][y] && (!vis[x][y] || t.k - 1 >= v[x][y]) && t.k - 1 >= 0) {
				v[x][y] = t.k - 1;
				vis[x][y] = true;
				q.push(Lan(x, y, t.k - 1, t.d + 1));
			}
			else if (inside(x, y) && !vis[x][y] && !map[x][y]) {
				vis[x][y] = true;
				q.push(Lan(x, y, k, t.d + 1));
			}
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &m, &n, &k);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &map[i][j]);
		if (!bfs())
			printf("-1\n");
	}
	return 0;
}