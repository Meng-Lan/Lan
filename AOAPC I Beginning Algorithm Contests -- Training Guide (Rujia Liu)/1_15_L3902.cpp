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
typedef unsigned long long ull;
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
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }
std::vector<int> Eratosthenes(const int len, int *vis) {
	memset(vis, 0, sizeof(int)*len);
	std::vector<int> prime;
	int m = (int)sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n, int *phi) {
	For(i, 2, n) phi[i] = 0;
	phi[1] = 1;
	For(i, 2, n) if (!phi[i])
		for (int j = i; j <= n; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i*(i - 1);
		}
}

const int maxn = 1000 + 10;
int n, s, k, fa[maxn], vis[maxn];
std::vector<int> G[maxn], deep[maxn];

void dfs(int f, int u, int d) {
	deep[d].push_back(u);
	fa[u] = f;
	FOR(i, 0, G[u].size()) if (G[u][i] != f) {
		dfs(u, G[u][i], d + 1);
	}
}

void dfs2(int f, int u, int d) {
	vis[u] = 1;
	if (d == 0) return;
	FOR(i, 0, G[u].size()) if(G[u][i]!=f)
		dfs2(u, G[u][i], d - 1);
}

int solve() {
	memset(vis, 0, sizeof(vis));
	//dfs2(-1, s, k);
	int ans = 0;
	for (int d = n - 1; d > k; --d) FOR(i, 0, deep[d].size()) {
		int &u = deep[d][i];
		if (vis[u] || G[u].size() > 1) continue;
		int v = u;
		FOR(i, 0, k) v = fa[v];
		dfs2(-1, v, k);
		++ans;
		//printf("u:%d v:%d\n", u,v);
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &s, &k);
		For(i, 0, n) { G[i].clear(); deep[i].clear(); }
		int u, v;
		FOR(i, 1, n) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(-1, s, 0);
		printf("%d\n", solve());
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}