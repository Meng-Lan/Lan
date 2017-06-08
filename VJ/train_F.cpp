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
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 210;
const int INF=1e9;
int x[maxn], y[maxn], n, vis[maxn][maxn], inq[maxn];
double d[maxn], dist[maxn][maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		For(i, 1, n) scanf("%d%d", x + i, y + i);
		For(i, 1, n) For(j, 1, i) dist[i][j] = dist[j][i] = sqrt((double)(x[i] - x[j])*(x[i] - x[j]) + (double)(y[i] - y[j])*(y[i] - y[j]));
		For(i, 2, n) d[i] = std::max(dist[1][i], dist[2][i]);
		memset(inq, 0, sizeof(inq));
		std::queue<int> q; q.push(1); inq[1] = 1; inq[2] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			For(i, 3, n) if (std::max(dist[u][i], dist[i][2]) < d[i]) {
				if (!inq[i]) q.push(i);
				d[i] = std::max(dist[u][i], dist[i][2]);
			}
		}
		For(i, 3, n) d[2] = std::min(d[2], d[i]);
		printf("Scenario #%d\n", ++kase);
		printf("Frog Distance = %.3f\n", d[2]); putchar('\n');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}