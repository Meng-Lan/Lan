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
#define mp make_pair
const int maxn = 505;
const int maxa = 55;
int n, val[maxn], pi[maxa][maxa];
bool vis[maxn];
vector<int> G[maxn],T[maxn],S[maxn];

inline int gcd(int a, int b) {
	return b ? gcd(b, a%b) : a;
}

bool operator<(const P &a, const P &b) {
	return a.first < b.first || a.first == b.first&&a.second < b.second;
}

int bfs(int u, int v) {
	memset(vis, 0, sizeof(vis));
	vis[u] = true;
	P start = mp(0,u);
	priority_queue<P> q;
	q.push(start);
	while (!q.empty()) {
		P s = q.top(); q.pop();
		if (s.second == v) return -s.first;
		for (auto &t : G[s.second])
			if (!vis[t]) {
				vis[t] = true;
				q.push(mp(s.first - 1, t));
			}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < maxa; ++i)
		for (int j = 1; j < maxa; ++j)
			if (gcd(i, j) == 1) pi[i][j] = 1;
			else
				pi[i][j] = 0;
	for (int i = 1; i <= n; ++i)
		scanf("%d", val + i);
	int u, v;
	FOR(i, n - 1) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
			if (pi[val[i]][val[j]]) {
				T[i].push_back(j);
			}
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
		for (auto &t : T[i]) {
			//cout << i << ' ' << t << endl;
			ans += bfs(i, t);
		}
	printf("%lld\n", ans);
	return 0;
}