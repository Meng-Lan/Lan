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

const int M = 8;
const int maxn = 305;
const int INF = 1e9;
int n, m;
int dp[maxn][maxn][maxn], tmp[maxn][maxn], now[maxn][maxn];


int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &m);
	For (d,0,M) For(i, 1, n) For(j, 1, n) dp[d][i][j] = -INF*(i != j);
	FOR(i, 0, m) {
		int x, y; scanf("%d%d", &x, &y);
		scanf("%d%d", &dp[0][x][y], &dp[0][y][x]);
	}
	For(d, 1, M) {
		For(i, 1, n) For(j, 1, n) For(k, 1, n)
			if (dp[d-1][i][j] > -INF&&dp[d-1][j][k] > -INF)
				dp[d][i][k] = std::max(dp[d][i][k], dp[d-1][i][j] + dp[d-1][j][k]);
	}
	int ans = 0;
	For(i, 1, n) For(j, 1, n) now[i][j] = -INF*(i != j);
	for (int d = M; d >= 0; --d) {
		For(i, 1, n) For(j, 1, n) tmp[i][j] = -INF*(i != j);
		For(i, 1, n) For(j, 1, n) For(k, 1, n)
			if (now[i][j] > -INF&&dp[d][j][k] > -INF)
				tmp[i][k] = std::max(tmp[i][k], now[i][j] + dp[d][j][k]);
		int isok = 0;
		For(i, 1, n) isok |= (tmp[i][i] > 0);
		if (!isok) {
			For(i, 1, n) For(j, 1, n) now[i][j] = tmp[i][j];
			ans += (1 << d);
		}
	}
	cout << (ans < n ? ans + 1 : 0) << endl;

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}