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
struct Point {
	int x, y;
	bool operator< (const Point &t)const {
		return x < t.x;
	}
}p[maxn];
int n, m, y[maxn], on[maxn], on2[maxn], left[maxn];

int solve() {
	std::sort(p, p + n);
	std::sort(y, y + n);
	m = std::unique(y, y + n) - y;
	if (m <= 2) return n;
	int ans = 0;
	FOR(i, 0, m) FOR(j, i + 1, m) {
		int miny = y[i], maxy = y[j];
		int k = 0;
		FOR(l, 0, n) {
			if (l == 0 || p[l - 1].x != p[l].x) {
				++k;
				on[k] = on2[k] = 0;
				left[k] = k == 0 ? 0 : left[k - 1] - on[k - 1] + on2[k - 1];
			}
			if (p[l].y > miny&&p[l].y < maxy) ++on[k];
			if (p[l].y >= miny&&p[l].y <= maxy) ++on2[k];
		}
		if (k <= 2) return n;
		int M = 0;
		For(l, 1, k) {
			ans = std::max(ans, left[l] + on2[l] + M);
			M = std::max(M, on[l] - left[l]);
		}
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) && n) {
		FOR(i, 0, n) {
			scanf("%d%d", &p[i].x, &p[i].y);
			y[i] = p[i].y;
		}
		printf("Case %d: %d\n", ++kase, solve());
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}