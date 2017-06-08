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

const int maxn = 105;
const int INF = 1e8;
int p[maxn], u[maxn*maxn], v[maxn*maxn], w[maxn*maxn], r[maxn*maxn], n, m;

int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
bool cmp(const int l, const int r) { return w[l] < w[r]; }

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &m) == 2 && n) {
		if (m == 0) {
			puts("-1"); continue;
		}
		For(i, 1, m) scanf("%d %d %d", u + i, v + i, w + i);
		For(i, 1, m) r[i] = i;
		std::sort(r + 1, r + m + 1, cmp);
		//For(i, 1, m) printf("#%d %d\n", i, r[i]);
		int ans = INF;
		For(L, 1, m) {
			For(i, 1, n) p[i] = i;
			int t = L;
			For(R, L, m) {
				int e = r[R], x = find(u[e]), y = find(v[e]);
				if (x != y) { p[x] = y; t = R; }
			}
			int x = find(1), ok = 0;
			For(i, 2, n) if (find(i) != x) ok = 1;
			if (ok) break;
			ans = std::min(ans, std::abs(w[r[t]] - w[r[L]]));
			//printf("L:%d R:%d ans:%d\n", L, t, ans);
		}
		if (ans == INF) puts("-1");
		else printf("%d\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}