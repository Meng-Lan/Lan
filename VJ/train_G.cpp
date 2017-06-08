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

const int maxn = 100010;
const int INF = 1e9;
int k, n, d[maxn], vis[maxn];

bool check(int x) { return x >= 0 && x < maxn; }

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	memset(d, 0x3f, sizeof(d));
	scanf("%d%d", &k, &n);
	std::queue<P> q; q.push(mp(k, 0)); vis[k] = 1;
	while (!q.empty()) {
		P u = q.front(); q.pop();
		d[u.first] = u.second;
		if (u.first == n) break;
		if (check(u.first * 2)) if (!vis[u.first * 2]) { q.push(mp(u.first * 2, u.second + 1)); vis[u.first * 2] = 1; }
		if (check(u.first + 1)) if (!vis[u.first + 1]) { q.push(mp(u.first + 1, u.second + 1)); vis[u.first + 1] = 1; }
		if (check(u.first - 1)) if (!vis[u.first - 1]) { q.push(mp(u.first - 1, u.second + 1)); vis[u.first - 1] = 1; }
	}
	printf("%d\n", d[n]);

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}