#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 110;
int color[maxn], diff[maxn];
int G[maxn][maxn], n, cnt;
std::vector<int> team[maxn][2];

bool dfs(int u, int k) {
	team[cnt][k - 1].push_back(u); color[u] = k;
	FOR(v, 0, n) if (u != v&&!(G[u][v] && G[v][u])) {
		if (color[v]>0 && color[u] == color[v]) return false;
		if (!color[v] && !dfs(v, 3 - k)) return false;
	}
	return true;
}

bool build_graph() {
	cnt = 0; memset(color, 0, sizeof(color));
	FOR(i, 0, n) if (!color[i]) {
		team[cnt][0].clear(); team[cnt][1].clear();
		if (!dfs(i, 1)) return false;
		diff[cnt] = team[cnt][0].size() - team[cnt][1].size();
		++cnt;
	}
	return true;
}

int d[maxn][2 * maxn];

void print(int ans) {
	std::vector<int> team1, team2;
	for (int i = cnt - 1; i >= 0; --i) {
		int t;
		if (d[i][ans - diff[i] + n]) { t = 0; ans -= diff[i]; }
		else { t = 1; ans += diff[i]; }
		for (auto &u : team[i][t]) team1.push_back(u);
		for (auto &u : team[i][1 ^ t]) team2.push_back(u);
	}
	printf("%d", team1.size());
	for (auto &u : team1) printf(" %d", u + 1);
	putchar('\n');

	printf("%d", team2.size());
	for (auto &u : team2) printf(" %d", u + 1);
	putchar('\n');
}

void dp() {
	memset(d, 0, sizeof(d));
	d[0][n] = 1;
	FOR(i, 0, cnt) {
		for (int j = -n; j <= n; ++j) if (d[i][j + n]) {
			d[i + 1][j + diff[i] + n] = 1;
			d[i + 1][j - diff[i] + n] = 1;
		}
	}
	for (int ans = 0; ans <= n; ++ans) {
		if (d[cnt][ans + n]) { print(ans); return; }
		if (d[cnt][-ans + n]) { print(ans); return; }
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); memset(G, 0, sizeof(G));
		FOR(i, 0, n) {
			int t; while (scanf("%d", &t) == 1 && t) G[i][t - 1] = 1;
		}
		if (n == 1 || !build_graph()) printf("No solution\n");
		else dp();
		if (T) putchar('\n');
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}