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
const int INF = 1 << 30;
int n, d[2][maxn][2], x[maxn], di[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1) {
		FOR(i, 0, n) { scanf("%d%d", x + i, di + i); d[0][i][0] = d[0][i][1] = 0; }
		int t = 0;
		FOR(i, 1, n) {
			FOR(j, 0, n - i) {
				d[t ^ 1][j][0] = std::min(d[t][j + 1][0] + x[j + 1] - x[j], d[t][j + 1][1] + x[j + i] - x[j]);
				if (d[t ^ 1][j][0] >= di[j]) d[t ^ 1][j][0] = INF;
				d[t ^ 1][j][1] = std::min(d[t][j][0] + x[j + i] - x[j], d[t][j][1] + x[j + i] - x[j + i - 1]);
				if (d[t ^ 1][j][1] >= di[j + i]) d[t ^ 1][j][1] = INF;
			}
			t ^= 1;
		}
		int ans = std::min(d[t][0][0], d[t][0][1]);
		if (ans >= INF) printf("No solution\n");
		else printf("%d\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}