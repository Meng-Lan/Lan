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

const int maxn = 100010;
int in[maxn], n, k, vis[maxn], sum;
ll ans;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &k);
	For(i, 1, n) { scanf("%d", in + i); sum += in[i]; }
	For(i, 1, n) ans += in[i] * in[i%n + 1];
	int t;
	FOR(i, 0, k) {
		scanf("%d", &t);
		int dis[3] = { t - 1,t,t + 1 };
		if (dis[0] == 0) dis[0] = n;
		if (dis[2] == n + 1) dis[2] = 1;
		int tot = 0;
		FOR(j, 0, 3) if (!vis[dis[j]])tot += in[dis[j]];
		ans += (ll)in[t] * (sum - tot);
		sum -= in[t]; vis[t] = 1;
	}
	printf("%I64d\n", ans);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}