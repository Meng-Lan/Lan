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

const int maxn = 10010;
int n, a, b, d[4][maxn], vis[4][maxn], cnt;
std::vector<int> G[maxn];

/*
状态:
d[0][i]==i与其父节点的边被覆盖
d[1][i]==i点及其所有边被覆盖
d[2][i]==i点与其父节点的边未被覆盖
d[3][i]==i点至其祖父节点的边未被覆盖，所以该点应使用B装置--(只是为了强制使用B装置)
转移方式：
d[0][i]=min(sum(d[0][v])+a,sum(d[1][v])+b,sum(d[2][v]),sum(d[0][v])-d[0][v']+d[3][v']);
d[1][i]=min(sum(d[0][v]),sum(d[1][v])+b);
d[2][i]=min(sum(d[0][v])+a,sum(d[0][v])-d[0][v']+d[3][v']);
d[3][i]=min(sum(d[1][v])+b);
*/

int dp(int s, int u, int fa) {
	int &ans = d[s][u];
	if (vis[s][u] == cnt) return ans;
	vis[s][u] = cnt;
	ans = 0;
	if (s == 0) {
		int tmp1 = 0, tmp2 = 0, tmp3 = 0;
		FOR(i, 0, G[u].size()) if (G[u][i] != fa) { tmp1 += dp(0, G[u][i], u); tmp2 += dp(1, G[u][i], u); tmp3 += dp(2, G[u][i], u); }
		ans = std::min(tmp1 + a, std::min(tmp2 + b, tmp3));
		FOR(i, 0, G[u].size()) if (G[u][i] != fa) ans = std::min(ans, tmp1 - d[0][G[u][i]] + dp(3, G[u][i], u));
	}
	else if (s == 1) {
		int tmp = 0;
		FOR(i, 0, G[u].size()) if (G[u][i] != fa) { ans += dp(0, G[u][i], u); tmp += dp(1, G[u][i], u); }
		ans = std::min(ans, tmp + b);
	}
	else if (s == 2) {
		int tmp = 0;
		FOR(i, 0, G[u].size()) if (G[u][i] != fa) { tmp += dp(0, G[u][i], u); }
		ans = tmp + a;
		FOR(i, 0, G[u].size()) if (G[u][i] != fa) ans = std::min(ans, tmp - d[0][G[u][i]] + dp(3, G[u][i], u));
	}
	else if (s == 3) {
		FOR(i, 0, G[u].size()) if (G[u][i] != fa) ans += dp(1, G[u][i], u);
		ans += b;
	}
	//printf("s:%d u:%d fa:%d size:%d ans:%d\n", s, u, fa, G[u].size(), ans);
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d%d", &n, &a, &b) == 3 && n) {
		For(i, 0, n) G[i].clear(); ++cnt;
		int u, v;
		FOR(i, 0, n - 1) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		/*For(i, 1, n) {
			printf("u:%d v:", i);
			FOR(j, 0, G[i].size()) printf(" %d", G[i][j]);
			putchar('\n');
		}*/
		printf("%d\n", dp(0, 1, -1));
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}