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
#define mp make_pair
const int maxn = 150;
const int maxh = 16;
const int dx[] = { 1,0,-1,0,0 };
const int dy[] = { 0,1,0,-1,0 };
int w, h, n;
vector<int> G[maxn];
int s[3], t[3], d[maxn][maxn][maxn],vis[maxn][maxn][maxn];

int ID(int a, int b, int c) {
	return (a << 16) | (b << 8) | c;
}

bool exchange(const int &x, const int &xx, const int &y, const int &yy) {
	return xx == yy || x == yy&&y == xx;
}

int dbfs() {
	memset(d, -1, sizeof(d));
	memset(vis, 0, sizeof(vis));
	int start = ID(s[0], s[1], s[2]);
	int end = ID(t[0], t[1], t[2]);
	queue<int> q, p;
	q.push(start);
	d[s[0]][s[1]][s[2]] = 0;
	vis[s[0]][s[1]][s[2]] = 1;
	p.push(end);
	d[t[0]][t[1]][t[2]] = 0;
	vis[t[0]][t[1]][t[2]] = 2;
	int cnt = 0;
	while (!q.empty() || !p.empty()) {
		while (!q.empty()) {
			int tmp = q.front();
			int a = (tmp >> 16) & 0xff, b = (tmp >> 8) & 0xff, c = tmp & 0xff;
			if (d[a][b][c] > cnt) break;
			q.pop();
			//if (tmp == end) return d[a][b][c];
			for (auto &i : G[a])
				for (auto &j : G[b]) {
					if (exchange(a, i, b, j)) continue;
					for (auto &k : G[c]) {
						if (exchange(a, i, c, k)) continue;
						if (exchange(b, j, c, k)) continue;
						if (vis[i][j][k] == 1) continue;
						if (vis[i][j][k] == 2) return d[a][b][c] + d[i][j][k] + 1;
						d[i][j][k] = d[a][b][c] + 1;
						vis[i][j][k] = 1;
						q.push(ID(i, j, k));
					}
				}
		}
		while (!p.empty()) {
			int tmp = p.front();
			int a = (tmp >> 16) & 0xff, b = (tmp >> 8) & 0xff, c = tmp & 0xff;
			if (d[a][b][c] > cnt) break;
			p.pop();
			//if (tmp == end) return d[a][b][c];
			for (auto &i : G[a])
				for (auto &j : G[b]) {
					if (exchange(a, i, b, j)) continue;
					for (auto &k : G[c]) {
						if (exchange(a, i, c, k)) continue;
						if (exchange(b, j, c, k)) continue;
						if (vis[i][j][k] == 2) continue;
						if (vis[i][j][k] == 1) return d[a][b][c] + d[i][j][k] + 1;
						d[i][j][k] = d[a][b][c] + 1;
						vis[i][j][k] = 2;
						p.push(ID(i, j, k));
					}
				}
		}
		++cnt;
	}
	return -1;
}
int main() {
	string str[maxh];
	while (scanf("%d%d%d", &w, &h, &n) == 3 && w) {
		for (auto &t : G)
			t.clear();
		getline(cin, str[0]);
		for (int i = 0; i < h; i++)
			getline(cin, str[i]);
		int cnt = 0;
		int g[maxh][maxh];
		memset(g, -1, sizeof(g));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (str[i][j] != '#') {
					if (isupper(str[i][j])) t[str[i][j] - 'A'] = cnt;
					if (islower(str[i][j])) s[str[i][j] - 'a'] = cnt;
					g[i][j] = cnt++;
				}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (g[i][j] >= 0)
					for (int k = 0; k < 5; k++) {
						int x = i + dx[k];
						int y = j + dy[k];
						if (x >= 0 && x < h&&y >= 0 && y < w && g[x][y] >= 0)
							G[g[i][j]].push_back(g[x][y]);
					}
		if (n <= 2) {
			s[2] = t[2] = cnt;
			G[s[2]].push_back(t[2]);
			cnt++;
		}
		if (n <= 1) {
			s[1] = t[1] = cnt;
			G[s[1]].push_back(t[1]);
			cnt++;
		}
		printf("%d\n", dbfs());
	}
	return 0;
}
/*
5 5 2
#####
#A#B#
#   #
#b#a#
#####
16 4 3
################
## ########## ##
#    ABCcba    #
################
16 16 3
################
### ##    #   ##
##  #  ##   # c#
#  ## ########b#
# ##  # #   #  #
#  # ##   # # ##
##  a#  # # #  #
### ## #### ## #
##   #   #  #  #
#  ##### # ## ##
####   #B# #   #
##  C#   #   ###
#  # # ####### #
# ######  A##  #
#        #    ##
################
0 0 0
*/