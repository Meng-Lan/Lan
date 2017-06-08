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

const int maxn = 2e5 + 10;
int d[maxn][25], in[maxn], n, m, k;
P p[maxn];

int RMQ(int l, int r) {
	int k = 0;
	while ((1 << (k + 1)) <= r - l + 1) ++k;
	return std::min(d[l][k], d[r - (1 << k) + 1][k]);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &k);
	For(i, 1, n) scanf("%d", in + i);
	For(i, 1, n) d[i][0] = in[i];
	for (int j = 1; (1<<j) <=n; ++j) {
		for (int i = 0; i + (1 << j) - 1 < n; i++) d[i][j] = std::min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
	}
	scanf("%d", &m);
	FOR(i, 0, m) scanf("%d%d", &p[i].first, &p[i].second);
	int ans = 0;
	FOR(i, 0, m) FOR(j, i + 1, m) {
		int low = RMQ(p[i].first, p[j].first);
		int sum = std::abs(p[i].first - p[j].first) + p[i].second + p[j].second - 2 * low;
		if (sum <k) ++ans;
	}
	cout << ans << '\n';

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}