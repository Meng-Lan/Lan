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
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 25;
const int INF = 1e9;
int d[maxn][maxn][maxn][maxn], tot[maxn][maxn][maxn][maxn];
int G[maxn][maxn], n, m, k;

int dp(int x, int y, int xx, int yy) {
	if (!tot[x][y][xx][yy]) {
		int cnt = 0;
		FOR(i, x, xx) FOR(j, y, yy) if (G[i][j]) ++cnt;
		tot[x][y][xx][yy] = cnt;
	}
	if (tot[x][y][xx][yy] == 1) return 0;
	if (!tot[x][y][xx][yy]) return INF;
	int &ans = d[x][y][xx][yy];
	if (ans >= 0) return ans;
	ans = INF;
	FOR(i, x, xx) ans = std::min(ans, dp(x, y, i, yy) + dp(i, y, xx, yy) + yy - y);
	FOR(i, y, yy) ans = std::min(ans, dp(x, y, xx, i) + dp(x, i, xx, yy) + xx - x);
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		int x, y; memset(G, 0, sizeof(G)); memset(tot, 0, sizeof(tot));
		FOR(i, 0, k) { scanf("%d%d", &x, &y); G[x][y] = 1; }
		/*For(i, 1, n + 1) For(j, 1, n + 1) {
			int cnt = 0;
			FOR(k, i, n + 1) FOR(l, i, n + 1) {
				if (G[k][l]) ++cnt;
				tot[i][j][k][l] = cnt;
			}
		}*/
		memset(d, -1, sizeof(d));
		printf("Case %d: ", ++kase);
		if (k > 1) printf("%d\n", dp(1, 1, n + 1, m + 1));
		else printf("0\n");
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}