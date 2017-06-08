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

const int maxn = 105;
const int INF = 1e9;
int in[maxn], n, d[2 * maxn][2 * maxn], cost[2 * maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	For(i, 1, n) scanf("%d", in + i);
	cost[0] = 0; For(i, 1, 2 * n) cost[i] = cost[i - 1] + in[((i - 1) % n + 1)];
	//For(i, 0, 2 * n) printf("#%d cost:%d\n", i, cost[i]);
	memset(d, 0x3f, sizeof(d));
	For(i, 1, 2 * n) d[i][i] = 0;
	FOR(l, 1, n) For(i, 1, 2 * n - l) {
		int j = i + l;
		FOR(k, i, j) d[i][j] = std::min(d[i][j], d[i][k] + d[k + 1][j] + cost[j] - cost[i - 1]);
	}
	int ans = INF;
	For(i, 1, n) ans = std::min(ans, d[i][i + n - 1]);
	printf("%d\n", ans);
	memset(d, 0, sizeof(d));
	For(i, 1, n) d[i][i] = 0;
	FOR(l, 1, n) For(i, 1, 2 * n - l) {
		int j = i + l;
		FOR(k, i, j) d[i][j] = std::max(d[i][j], d[i][k] + d[k + 1][j] + cost[j] - cost[i - 1]);
	}
	ans = 0;
	For(i, 1, n) ans = std::max(ans, d[i][i + n - 1]);
	printf("%d\n", ans);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}