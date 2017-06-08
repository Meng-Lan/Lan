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

//边框整体+1，有可能会出现1封闭掉了边界0，但实际不属于封闭空间内

using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define mp make_pair
const int maxn = 35;
const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };
int p[maxn][maxn],vis[maxn][maxn], n;

bool check(int x, int y) {
	return x >= 0 && x <= n + 1 && y >= 0 && y <= n + 1 && !vis[x][y];
}

void bfs(P start, int t) {
	queue<P> q;
	q.push(start);
	while (!q.empty()) {
		P u = q.front();
		q.pop();
		p[u.first][u.second] = t;
		for (int i = 0; i < 4; i++) {
			int x = u.first + dx[i];
			int y = u.second + dy[i];
			if (check(x, y) && !p[x][y]) {
				vis[x][y] = 1;
				q.push(mp(x, y));
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &p[i][j]);
	bfs(mp(0, 0), -1);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			if (!p[i][j]) {
				bfs(mp(i, j), 2);
			}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			printf("%d ", p[i][j] == -1 ? 0 : p[i][j]);
		putchar('\n');
	}
	return 0;
}