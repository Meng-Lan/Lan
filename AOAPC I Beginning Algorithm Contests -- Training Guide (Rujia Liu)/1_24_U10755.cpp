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

const int maxn = 25;
const ll INF = 1L << 60;
ll S[maxn][maxn][maxn];
int n, x, y, z, a, b, c;

void expend(int t, int &a, int &b, int &c) {
	a = t & 1; t >>= 1;
	b = t & 1; t >>= 1;
	c = t & 1;
}

int sign(int a, int b, int c) {
	return (a + b + c) % 2 ? 1 : -1;
}

ll sum (int x1, int x2, int y1, int y2, int z1, int z2) {
	int dx = x2 - x1 + 1, dy = y2 - y1 + 1, dz = z2 - z1 + 1;
	ll s = 0;
	FOR(i, 0, 8) {
		int a, b, c;
		expend(i, a, b, c);
		s -= S[x2 - a*dx][y2 - b*dy][z2 - c*dz] * sign(a, b, c);
	}
	return s;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	while (n--) {
		scanf("%d%d%d", &x, &y, &z);
		For(i, 1, x) For(j, 1, y) For(k, 1, z) scanf("%lld", &S[i][j][k]);
		For(i, 1, x) For(j, 1, y) For(k, 1, z) For(l, 1, 7) {
			expend(l, a, b, c);
			S[i][j][k] += S[i - a][j - b][k - c] * sign(a, b, c);
		}
		ll ans = -INF;
		For(x1, 1, x) For(x2, x1, x) For(y1, 1, y) For(y2, y1, y) {
			ll M = 0;
			For(i, 1, z) {
				ll s = sum(x1, x2, y1, y2, 1, i);
				ans = std::max(ans, s - M);
				M = std::min(M, s);
			}
		}
		printf("%lld\n", ans);
		if (n) putchar('\n');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}