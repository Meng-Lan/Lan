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

const int maxn = 105;
const int INF = 1e9;
int in[maxn][15], n, m, d[maxn][15], next[maxn][15];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &m, &n) == 2 && n&&m) {
		FOR(i, 0, m) FOR(j, 0, n) scanf("%d", in[j] + i);
		int ans = INF, first = 0;
		for (int i = n - 1; i >= 0; --i)
			FOR(j, 0, m) {
			if (i == n - 1) d[i][j] = in[i][j];
			else {
				int y[3] = { j,j - 1,j + 1 };
				if (y[0] == 0) y[1] = m - 1;
				if (y[0] == m - 1) y[2] = 0;
				std::sort(y, y + 3);
				d[i][j] = INF;
				FOR(k, 0, 3) {
					int v = d[i + 1][y[k]] + in[i][j];
					if (v < d[i][j]) { d[i][j] = v; next[i][j] = y[k]; }
				}
			}
			if (i == 0 && d[i][j] < ans) { ans = d[i][j]; first = j; }
		}
		for (int i = 0, j = first; i < n; j = next[i][j], ++i) printf("%d%c", j + 1, (i != n - 1) ? ' ' : '\n');
		printf("%d\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}