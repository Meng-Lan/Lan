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
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int INF = 1e9;
const int maxn = 5010;

char p[maxn], q[maxn];
int sp[26], sq[26], ep[26], eq[26];
int d[2][maxn], c[2][maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf(" %s %s", p + 1, q + 1);
		int n = strlen(p + 1), m = strlen(q + 1);
		For(i, 1, n) p[i] -= 'A'; For(i, 1, m) q[i] -= 'A';

		FOR(i, 0, 26) { sp[i] = sq[i] = INF; ep[i] = eq[i] = 0; }
		For(i, 1, n) {
			sp[p[i]] = std::min(sp[p[i]], i);
			ep[p[i]] = i;
		}
		For(i, 1, m) {
			sq[q[i]] = std::min(sq[q[i]], i);
			eq[q[i]] = i;
		}

		int t = 0;
		memset(c, 0, sizeof(c)); memset(d, 0, sizeof(d));
		For(i, 0, n) {
			For(j, 0, m) {
				if (!i&&!j) continue;
				int v1 = INF, v2 = INF;
				if (i) v1 = d[t ^ 1][j] + c[t ^ 1][j];
				if (j) v2 = d[t][j - 1] + c[t][j - 1];
				d[t][j] = std::min(v1, v2);

				if (i) {
					c[t][j] = c[t ^ 1][j];
					if (sp[p[i]] == i&&sq[p[i]] > j) ++c[t][j];
					if (ep[p[i]] == i&&eq[p[i]] <= j) --c[t][j];
				}
				else if (j) {
					c[t][j] = c[t][j - 1];
					if (sq[q[j]] == j&&sp[q[j]] > i) ++c[t][j];
					if (eq[q[j]] == j&&ep[q[j]] <= i) --c[t][j];
				}
			}
			t ^= 1;
		}
		printf("%d\n", d[t ^ 1][m]);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}