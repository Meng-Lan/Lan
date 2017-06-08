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

const int maxn = 1005;
int in[maxn], D[maxn * 10], n, sum;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	FOR(i, 0, n) {
		int u, v; scanf("%d%d", &u, &v);
		in[i] = u - v; sum += in[i];
	}
	int *d = &D[5 * maxn];
	d[-sum] = 1;
	const int len = 5 * maxn - 1;
	FOR(i, 0, n) {
		if (in[i] > 0) {
			for (int j = len; j >= -len; --j) if (d[j] > 0) {
				if (d[j + in[i]] > 0) d[j + in[i]] = std::min(d[j] + 1, d[j + in[i]]);
				else d[j + in[i]] = d[j] + 1;
			}
		}
		else if (in[i] < 0)
			for (int j = -len; j < len; ++j) if (d[j]>0) {
				if (d[j + in[i]] > 0) d[j + in[i]] = std::min(d[j] + 1, d[j + in[i]]);
				else d[j + in[i]] = d[j] + 1;
			}
	}
	int ans = 1e9;
	FOR(i, 0, len) if (d[i] > 0 || d[-i] > 0) {
		if (d[i] > 0) ans = std::min(ans, d[i]);
		if (d[-i] > 0) ans = std::min(ans, d[-i]);
		break;
	}
	printf("%d\n", ans - 1);



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}