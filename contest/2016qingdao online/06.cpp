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

const int maxn = 1e5 + 10;
const int maxm = 5e5 + 10;
std::vector<int> G[maxn];
std::vector<P> edge;
int vis[maxm], cnt[maxn], num[maxn], n, m, kase;

void dfs(int u) {
	++cnt[u];
	FOR(i, 0, G[u].size()) {
		int e = G[u][i];
		if (vis[e]!=kase) {
			vis[e] = kase;
			P &E = edge[e];
			if (E.first == u) return dfs(E.second);
			else return dfs(E.first);
		}
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		++kase;
		scanf("%d%d", &n, &m);
		For(i, 1, n) scanf("%d", num + i);
		memset(cnt, 0, sizeof(int)*(n + 2));
		For(i, 1, n) G[i].clear(); edge.clear();
		int u, v;
		FOR(i, 0, m) {
			scanf("%d%d", &u, &v);
			G[u].push_back(i);
			G[v].push_back(i);
			edge.push_back(mp(u, v));
		}

		dfs(1);
		bool ok = true;
		FOR(i, 0, m) if (vis[i] != kase) {
			ok = false;
			break;
		}
		if (!ok) printf("Impossible\n");
		else {
			int ans = 0;
			For(i, 1, n) {
				int &len = cnt[i];
				if (len & 1) ans ^= num[i];
			}
			printf("%d\n", ans);
		}
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}