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
const int maxt = 205;
const int INF = 1e9;
int t[maxn], has_train[maxt][maxn][2], n, T, dp[maxt][maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		memset(has_train, 0, sizeof(has_train));
		scanf("%d", &T);
		FOR(i, 1, n) scanf("%d", t + i);
		int m; scanf("%d", &m);
		FOR(i, 0, m) {
			int tmp; scanf("%d", &tmp);
			FOR(j, 1, n) {
				if (tmp <= T) has_train[tmp][j][0] = 1;
				tmp += t[j];
			}
		}
		scanf("%d", &m);
		FOR(i, 0, m) {
			int tmp; scanf("%d", &tmp);
			for (int j = n - 1; j >= 1; --j) {
				if (tmp <= T) has_train[tmp][j + 1][1] = 1;
				tmp += t[j];
			}
		}
		FOR(i, 1, n) dp[T][i] = INF;
		dp[T][n] = 0;
		for (int i = T - 1; i >= 0; --i)
			For(j, 1, n) {
			dp[i][j] = dp[i + 1][j] + 1;
			if (j < n&&has_train[i][j][0] && i + t[j] <= T)
				dp[i][j] = std::min(dp[i][j], dp[i + t[j]][j + 1]);
			if (j > 1 && has_train[i][j][1] && i + t[j - 1] <= T)
				dp[i][j] = std::min(dp[i][j], dp[i + t[j - 1]][j - 1]);
		}
		printf("Case Number %d: ", ++kase);
		if (dp[0][1] >= INF) printf("impossible\n");
		else printf("%d\n", dp[0][1]);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}