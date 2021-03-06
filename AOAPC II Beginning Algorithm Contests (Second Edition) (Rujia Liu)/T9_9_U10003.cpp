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

const int maxn = 55;
const int INF = 1e9;
int in[maxn], d[maxn][maxn], vis[maxn][maxn];

int dp(int l, int r) {
	int &ans = d[l][r];
	if (ans >= 0) return ans;
	ans = INF;
	FOR(i, l + 1, r) ans = std::min(ans, dp(l, i) + dp(i, r) + in[r] - in[l]);
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int L, n;
	while (scanf("%d", &L) == 1 && L) {
		scanf("%d", &n);
		For(i, 1, n) scanf("%d", in + i);
		in[0] = 0; in[n + 1] = L;
		memset(d, -1, sizeof(d));
		For(i, 0, n + 1) d[i][i] = 0;
		FOR(i, 0, n + 1) d[i][i + 1] = 0;
		printf("The minimum cutting is %d.\n", dp(0, n + 1));
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}