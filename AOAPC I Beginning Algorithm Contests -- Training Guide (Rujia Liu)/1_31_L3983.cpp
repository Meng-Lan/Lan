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

const int maxn = 1e5 + 10;
int c, n, d[maxn], x[maxn], y[maxn], w[maxn], vis[maxn];

int dp(int i) {
	if (i <= 0) return 0;
	if (vis[i]) return d[i];
	vis[i] = 1;
	int tmp = w[i];
	int cost = std::abs(x[i]) + std::abs(y[i]);
	int &ans = d[i];
	ans = 2 * cost + dp(i - 1);
	for (int j = i - 1; j >= 0; --j)
		if (tmp + w[j] <= c) {
			tmp += w[j];
			cost += std::abs(x[j + 1] - x[j]) + std::abs(y[j + 1] - y[j]);
			ans = std::min(ans, cost + dp(j - 1) + std::abs(x[j]) + std::abs(y[j]));
		}
		else break;
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &c, &n);
		x[0] = y[0] = 0;
		memset(vis, 0, sizeof(vis));
		For(i, 1, n) scanf("%d%d%d", x + i, y + i, w + i);
		printf("%d\n", dp(n));
		if (T) putchar('\n');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}