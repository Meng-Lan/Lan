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
std::vector<int> sons[maxn];
int n, T;

int dp(int u) {
	if (sons[u].empty()) return 1;
	int ans = 0, k = sons[u].size();
	std::vector<int> d;
	FOR(i, 0, k) d.push_back(dp(sons[u][i]));
	std::sort(d.begin(), d.end());
	int c = (k*T - 1) / 100 + 1;
	FOR(i, 0, c) ans += d[i];
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &T) == 2 && n&&T) {
		For(i, 0, n) sons[i].clear();
		{int t; FOR(i, 0, n) { scanf("%d", &t);sons[t].push_back(i + 1); }}
		printf("%d\n", dp(0));
	}







#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}