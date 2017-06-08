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

const int maxn = 205;
const int INF = 1e9;
int n, a, b, ans[maxn][maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &n, &a, &b);
	if (a == b) { puts("0"); return 0; }
	For(i, 1, n) For(j, 1, n) ans[i][j] = INF;
	int t;
	For(i, 1, n) {
		scanf("%d", &t);
		if (i - t >= 1) ans[i][i - t] = 1;
		if (i + t <= n) ans[i][i + t] = 1;
	}
	For(k, 1, n) For(i, 1, n) For(j, 1, n)
		if (ans[i][k] + ans[k][j] < ans[i][j]) ans[i][j] = ans[i][k] + ans[k][j];
	if (ans[a][b] == INF) printf("-1");
	else printf("%d\n", ans[a][b]);



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}