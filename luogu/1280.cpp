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

const int maxn = 10000 + 10;
struct Lan {
	int l, r;
	Lan(int l = 0, int r = 0) :l(l), r(r) {};
	bool operator<(const Lan &t) { return l < t.l || l == t.l&&r < t.r; }
	bool operator<(const int &t) { return l < t; }
}in[maxn];
int n, k, d[maxn];

int dp(int T) {
	int &ans = d[T];
	if (ans >= 0) return ans;
	if (T > n + 1) return 0;
	Lan *low = std::lower_bound(in, in + k, T);
	int len = 0;
	while (low + len != in + k && (low + len)->l == low->l) ans = std::max(ans, dp((low + len)->r) + low->l - T), ++len;
	if (low == in + k) ans = n - T + 1;
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &k);
	FOR(i, 0, k) scanf("%d%d", &in[i].l, &in[i].r), in[i].r += in[i].l;
	std::sort(in, in + k);
	memset(d, -1, sizeof(d));
	dp(1);
	printf("%d\n", d[1]);



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}