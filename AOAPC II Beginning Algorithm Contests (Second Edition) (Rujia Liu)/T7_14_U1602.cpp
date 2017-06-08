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
const int maxn = 11;
int n, w, h;
int G[maxn][maxn];
int cnt = 0;

const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };

inline bool check(const int &x,const int &y) {
	return x >= 0 && x < w&&y >= 0 && y < h;
}

set<vector<P> > repeat;
vector<P> sta, sta2;

inline void pb(const int &i,const int &j) {
	sta.push_back(mp(i, j));
	sta2.push_back(mp(j, i));
}

inline void init() {
	sta.clear(); sta2.clear();
}

inline void insert() {
	repeat.insert(sta); repeat.insert(sta2);
}

bool updata() {
	init();
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j)
			if (G[i][j] == 1)
				pb(i, j);
	if (repeat.count(sta)) return false;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++)
			printf("%d", G[i][j]);
		putchar('\n');
	}
	for (auto &t : sta)
		printf("%d %d\n", t.first, t.second);
	putchar('\n');
	insert(); init();
	for (int i = w - 1; i >= 0; --i)
		for (int j = 0; j < h; ++j)
			if (G[i][j] == 1)
				pb(i, j);
	for (auto &t : sta)
		printf("%d %d\n", t.first, t.second);
	putchar('\n');
	insert(); init();
	for (int i = 0; i < w; ++i)
		for (int j = h - 1; j >= 0; --j)
			if (G[i][j] == 1)
				pb(i, j);
	for (auto &t : sta)
		printf("%d %d\n", t.first, t.second);
	putchar('\n');
	insert(); init();
	for (int i = w - 1; i >= 0; --i)
		for (int j = h - 1; j >= 0; --j)
			if (G[i][j] == 1)
				pb(i, j);
	for (auto &t : sta)
		printf("%d %d\n", t.first, t.second);
	putchar('\n');
	insert();
	return true;
}

void dfs(int x,int y,int d) {
	if (d == n) {
		if (updata()) cnt++;
		else return;
	}
	for (int i = 0; i < 4; i++) {
		int xx = x + dx[i];
		int yy = y + dy[i];
		if (check(xx,yy)&&!G[xx][yy]) {
			G[xx][yy] = 1;
			dfs(xx, yy, d + 1);
			G[xx][yy] = 0;
		}
	}
}

int main() {
	while (scanf("%d%d%d", &n, &w, &h)==3) {
		repeat.clear();
		memset(G, 0, sizeof(G));
		cnt = 0;
		w = min(n, w);
		h = min(n, h);
		for (int i = 0; i < h; i++) {
			dfs(i, 0, 0);
			G[i][0] = -1;
		}
		printf("%d\n", cnt);
		printf("%d\n", repeat.size());
	}
	return 0;
}