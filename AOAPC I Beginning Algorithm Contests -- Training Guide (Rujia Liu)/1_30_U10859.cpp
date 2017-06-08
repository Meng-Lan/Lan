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

const int maxn = 1010;
int n, m, d[maxn][2], vis[maxn][2];
std::vector<int> adj[maxn];

int dp(int i, int j, int f) {
	if (vis[i][j]) return d[i][j];
	vis[i][j] = 1;
	int &ans = d[i][j];
	ans = 2000;
	FOR(k, 0, adj[i].size())
		if (adj[i][k] != f) ans += dp(adj[i][k], 1, i);
	if (!j&&f >= 0) ans++;
	if (j || f < 0) {
		int sum = 0;
		FOR(k, 0, adj[i].size())
			if (adj[i][k] != f) sum += dp(adj[i][k], 0, i);
		if (j) sum++;
		ans = std::min(ans, sum);
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		For(i, 0, n) adj[i].clear();
		FOR(i, 0, m) {
			int x, y; scanf("%d%d", &x, &y);
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		memset(vis, 0, sizeof(vis));
		int ans = 0;
		FOR(i, 0, n)
			if (!vis[i][0])
				ans += dp(i, 0, -1);
		printf("%d %d %d\n", ans / 2000, m - ans % 2000, ans % 2000);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}