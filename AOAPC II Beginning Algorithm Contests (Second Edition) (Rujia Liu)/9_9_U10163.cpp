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

const int maxm = 35;
const int maxn = 105;
const int INF = 1e9;
int n, m, d[maxm][maxn], p[maxm], v[maxm][maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &m) == 2 && n&&m) {
		For(i, 1, m) scanf("%d", p + i);
		memset(d, 0, sizeof(d));
		For(i, 1, m) {
			d[i - 1][0] = INF;
			For(j, 1, n) {
				d[i][j] = d[i - 1][j];
				For(k, 1, j)
					d[i][j] = std::max(d[i][j], std::min(d[i - 1][j - k], p[i] / k));
			}
		}
		memset(v, 0x3f, sizeof(v));
		For(i, 1, m) {
			v[i - 1][0] = 0;
			For(j, 1, n) {
				v[i][j] = v[i - 1][j];
				For(k, 1, j) if (p[i] / k >= d[m][n])
					v[i][j] = std::min(v[i][j], v[i - 1][j - k] + p[i]);
			}
		}
		printf("%d %d\n", d[m][n], d[m][n] == 0 ? 0 : v[m][n]);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}