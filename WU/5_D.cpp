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

const int maxn = 1e3 + 5;
const int INF = 1e9;
int d[maxn], vis[maxn];
std::vector<P> G[maxn];
int n, m, x;

int dij(int from,int to) {
	memset(vis, 0, sizeof(vis));
	std::priority_queue<P> q;
	q.push(mp(0, from));
	while (!q.empty()) {
		P u = q.top(); q.pop();
		if (u.second == to) return -u.first;
		if (vis[u.second]) continue;
		vis[u.second] = 1;
		FOR(i, 0, G[u.second].size()) q.push(mp(u.first - G[u.second][i].second, G[u.second][i].first));
	}
	return -INF;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &n, &m, &x);
	int u, v, t;
	FOR(i, 0, m) {
		scanf("%d%d%d", &u, &v, &t);
		G[u].push_back(mp(v, t));
	}
	std::priority_queue<P> q;
	q.push(mp(0, x));
	while (!q.empty()) {
		P u = q.top(); q.pop();
		if (vis[u.second]) continue;
		vis[u.second] = 1;
		d[u.second] = -u.first;
		FOR(i, 0, G[u.second].size()) q.push(mp(u.first - G[u.second][i].second, G[u.second][i].first));
	}
	int ans = 0;
	For(i, 1, n) if (i != x) {
		//printf("#%d %d %d\n",i, dij(i, x), d[i]);
		ans = std::max(ans, dij(i, x) + d[i]);
	}
	printf("%d\n", ans);

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}