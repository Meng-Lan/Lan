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
const int maxn = 100000 + 10;
vector<P> G;
int vis[maxn];
int tmp[maxn];
int ans[maxn];
int n, m, cnt = 0;

bool dfs(int d,int u) {
	if (vis[u] == -1) return false;
	vis[u] = -1;
	G.push_back(mp(d, u));
	cnt++;
	if (tmp[u])
		if (!dfs(d+1,tmp[u])) return false;
	vis[u] = 1;
	return true;
}

bool topsort() {
	G.clear();
	memset(vis, 0, sizeof(vis));
	for (int i = n; i >= 1; i--)
		if (tmp[i])
			if (!dfs(1, i)) return false;
	return true;
}

bool cmp(const P &a, const P &b) {
	return a.first <= b.first&&a.second > b.second;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		int id;
		memset(tmp, 0, sizeof(tmp));
		for (int i = 0; i < m; i++) {
			scanf("%d", &id);
			scanf("%d", tmp + id);
		}
		topsort();
		sort(G.begin(), G.end(), cmp);
		for (int i = n,cnt=1; i >= 1;i--,cnt++){
			if (vis[i])
				ans[cnt] = i;
		putchar('\n');
		for (auto &t : G)
			cout << t.first << " " << t.second << endl;
		putchar('\n');
	}
	return 0;
}