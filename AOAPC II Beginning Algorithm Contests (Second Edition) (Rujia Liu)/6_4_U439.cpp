#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<utility>
#include<queue>
using namespace std;
typedef pair<int, int> P;
const int maxn = 8;
int vis[maxn][maxn], d[maxn][maxn];
char sbegin[maxn], send[maxn];
P u, v;

const int dr[] = { -1,-2,-2,-1,1,2,2,1 };
const int dc[] = { -2,-1,1,2,2,1,-1,-2 };

bool inside(const int &r,const int &c) {
	return r >= 0 && r < maxn&&c >= 0 && c < maxn;
}

int bfs(P &u, P &v) {
	memset(vis, 0, sizeof(vis));
	queue<P> q;
	q.push(u);
	vis[u.first][u.second] = true;
	d[u.first][u.second] = 0;
	P t;
	while (!q.empty()) {
		t = q.front();
		q.pop();
		if (t.first == v.first&&t.second == v.second)
			break;
		for (int i = 0; i < 8; i++) {
			int r = t.first + dr[i];
			int c = t.second + dc[i];
			if(inside(r,c))
				if (!vis[r][c]) {
					vis[r][c] = true;
					d[r][c] = d[t.first][t.second] + 1;
					q.push(make_pair(r, c));
				}
		}
	}
	return d[v.first][v.second];
}
int main() {
	while (scanf("%s %s", sbegin, send) == 2) {
		u.first = sbegin[0] - 'a';
		u.second = sbegin[1] - '1';
		v.first = send[0] - 'a';
		v.second = send[1] - '1';
		printf("To get from %s to %s takes %d knight moves.\n", sbegin, send, bfs(u, v));
	}
	return 0;
}