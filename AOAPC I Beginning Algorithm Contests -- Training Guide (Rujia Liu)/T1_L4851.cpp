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

const int maxn = 6e4 + 10;
P in[maxn];
int n, m, d[maxn];

inline int distance(int x, int y, int k) {
	return std::abs(x - in[k].first) + std::abs(y - in[k].second);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &m, &n);
		FOR(i, 0, n) scanf("%d%d", &in[i].first, &in[i].second);
		int l = std::min(in[0].first, in[1].first);
		int r = std::max(in[0].first, in[1].first);
		int y = in[0].second;
		For(i, l, r) d[i] = m;
		d[l] = d[r] = 0;
		FOR(i, 2, n)
			d[in[i].first] = std::min(d[in[i].first], std::abs(in[i].second - y));
		for (int i = r - 1; i >= l; --i) d[i] = std::min(d[i], d[i + 1] + 1);
		For(i, l + 1, r) d[i] = std::min(d[i], d[i - 1] + 1);
		//For(i, l, r) printf("d[%d]:%d\n", i, d[i]);
		ll ans = 0;
		For(i, l, r) if (d[i]) {
			++ans;
			ans += std::min(d[i] - 1, y);
			ans += std::min(d[i] - 1, m - y - 1);
		}
		printf("%lld\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}