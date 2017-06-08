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
std::vector<int> prime;
void Eratosthenes() {
	const int len = 1 << 16;
	int vis[len]; memset(vis, 0, sizeof(vis));
	int m = sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
}

const int maxn = 7000;
int e[maxn];
ll n;

int divide_all(ll &n, int d) {
	int x = 1;
	while (n%d == 0) { n /= d; x *= d; }
	return x;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	Eratosthenes();
	int kase = 0;
	while (cin >> n&&n) {
		printf("Case %d: ", ++kase);
		if (n == 1) { printf("2\n"); continue; }
		ll ans = 0, cnt = 0;
		for (auto &t : prime) if (n%t == 0) { ans += divide_all(n, t); ++cnt; }
		if (n > 1) { ++cnt; ans += n; }
		if (cnt < 2) ++ans;
		printf("%lld\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}