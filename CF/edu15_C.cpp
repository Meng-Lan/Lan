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

const int maxn = 1e5 + 10;
const int INF = 1e9;
ll cities[maxn], towers[maxn], n, m;

bool cmp(ll r) {
	int cnt = 0;
	FOR(i, 0, m) {
		if (cnt == n) break;
		while (cnt < n&&abs(cities[cnt] - towers[i]) <= r) ++cnt;
	}
	return cnt == n;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%I64d%I64d", &n, &m);
	FOR(i, 0, n) scanf("%I64d", cities + i);
	FOR(i, 0, m) scanf("%I64d", towers + i);
	std::sort(cities, cities + n);
	std::sort(towers, towers + m);
	ll l = 0, r = (1ll << 60);
	while (l < r) {
		ll m = l + (r - l) / 2;
		if (cmp(m)) r = m;
		else l = m + 1;
	}
	printf("%I64d\n", l);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}