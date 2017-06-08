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

const int maxn = 40;
int n, d[maxn][maxn];
ll c[maxn][maxn];
char s[maxn], t[maxn];


int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n); getchar();
	For(kase, 1, n) {
		gets(s + 1); gets(t + 1);
		//scanf(" %s %s", s + 1, t + 1);
		int lens = strlen(s + 1), lent = strlen(t + 1);
		memset(d, 0, sizeof(d)); memset(c, 0, sizeof(c));
		For(i, 0, lens) c[i][0] = 1; For(i, 0, lent) c[0][i] = 1;
		For(i, 1, lens) For(j, 1, lent) {
			if (s[i] == t[j]) { d[i][j] = d[i - 1][j - 1] + 1; c[i][j] = c[i - 1][j - 1]; }
			else {
				d[i][j] = std::max(d[i - 1][j], d[i][j - 1]);
				if (d[i - 1][j] > d[i][j - 1]) c[i][j] = c[i - 1][j];
				else if (d[i - 1][j] < d[i][j - 1]) c[i][j] = c[i][j - 1];
				else c[i][j] = c[i - 1][j] + c[i][j - 1];
			}
		}
		printf("Case #%d: %d %lld\n", kase, lens + lent - d[lens][lent], c[lens][lent]);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}