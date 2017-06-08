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
const int maxn = 150;
const int maxh = 16;
const int dx[] = { 1,0,-1,0,0 };
const int dy[] = { 0,1,0,-1,0 };
int w, h, n;
vector<int> G[maxn];
int s[3], t[3], d[maxn][maxn][maxn];

int ID(int a, int b, int c) {
	return (a << 16) | (b << 8) | c;
}

bool exchange(const int &x,const int &xx,const int &y,const int &yy) {
	return xx == yy || x == yy&&y == xx;
}

int bfs() {
	memset(d, -1, sizeof(d));
	int start = ID(s[0], s[1], s[2]);
	int end = ID(t[0], t[1], t[2]);
	queue<int> q;
	q.push(start);
	d[s[0]][s[1]][s[2]] = 0;
	while (!q.empty()) {
		int tmp = q.front();
		q.pop();
		int a = (tmp >> 16) & 0xff, b = (tmp >> 8) & 0xff, c = tmp & 0xff;
		if (tmp == end) return d[a][b][c];
		for (auto &i : G[a])
			for (auto &j : G[b]) {
				if (exchange(a, i, b, j)) continue;
				for (auto &k : G[c]) {
					if (exchange(a, i, c, k)) continue;
					if (exchange(b, j, c, k)) continue;
					if (d[i][j][k] != -1) continue;
					d[i][j][k] = d[a][b][c] + 1;
					q.push(ID(i, j, k));
				}
			}
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
		printf("%d\n", bfs());
	}
	return 0;
}