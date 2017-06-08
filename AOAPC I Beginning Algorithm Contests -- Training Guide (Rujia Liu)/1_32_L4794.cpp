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
std::vector<int> Eratosthenes(const int len, int *vis) {
	memset(vis, 0, sizeof(int)*len);
	std::vector<int> prime;
	int m = (int)sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n, int *phi) {
	For(i, 2, n) phi[i] = 0;
	phi[1] = 1;
	For(i, 2, n) if (!phi[i])
		for (int j = i; j <= n; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i*(i - 1);
		}
}

const int maxn = 16;
const int maxw = 100 + 10;
int n, x, y, in[maxn], sum[1 << maxn], vis[1 << maxn][maxw], d[1 << maxn][maxw];

int bitcount(int x) {
	return x ? bitcount(x / 2) + (x&1) : 0;
}

int dp(int s, int x) {
	if (vis[s][x]) return d[s][x];
	vis[s][x] = 1;
	int &ans = d[s][x];
	if (bitcount(s) == 1) return ans = 1;
	int y = sum[s] / x;
	for (int s0 = (s - 1)&s; s0; s0 = (s0 - 1)&s) {
		int s1 = s - s0;
		if (sum[s0] % x == 0 && dp(s0, std::min(x, sum[s0] / x)) && dp(s1, std::min(x, sum[s1] / x))) return ans = 1;
		if (sum[s0] % y == 0 && dp(s0, std::min(y, sum[s0] / y)) && dp(s1, std::min(y, sum[s1] / y))) return ans = 1;
	}
	return ans = 0;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d%d", &x, &y);
		FOR(i, 0, n) scanf("%d", in + i);
		memset(sum, 0, sizeof(sum));
		FOR(s, 0, 1 << n)
			FOR(i, 0, n) if (s&(1 << i)) sum[s] += in[i];
		memset(vis, 0, sizeof(vis));
		int ALL = (1 << n) - 1;
		int ans;
		if (sum[ALL] != x*y || sum[ALL] % x != 0) ans = 0;
		else ans = dp(ALL, std::min(x, y));
		printf("Case %d: %s\n", ++kase, ans ? "Yes" : "No");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}