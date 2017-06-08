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

const int maxn = 5005;
int in[maxn], d[1005][maxn], n, k;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &k, &n); k += 8;
		for (int i = n - 1; i >= 0; --i) scanf("%d", in + i);
		memset(d, 0x55, sizeof(d));
		FOR(i, 0, n) d[0][i] = 0;
		For(i, 1, k)FOR(j, i * 3 - 1, n) {
			d[i][j] = d[i][j - 1];
			if (d[i - 1][j - 2] + (in[j] - in[j - 1])*(in[j] - in[j - 1]) < d[i][j]) d[i][j] = d[i - 1][j - 2] + (in[j] - in[j - 1])*(in[j] - in[j - 1]);
		}
		printf("%d\n", d[k][n - 1]);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}