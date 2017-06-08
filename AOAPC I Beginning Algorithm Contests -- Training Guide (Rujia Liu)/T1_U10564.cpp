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

const int maxs = 500 + 5;
const int maxn = 45;
int in[maxn][maxn], vis[maxn][maxn][maxs], pos[maxn][maxn];
int n, s, kase;
ll d[maxn][maxn][maxs];

ll dp(int i, int j, int k) {
	if (pos[i][j] != kase) return 0;
	if (vis[i][j][k] == kase) return d[i][j][k];
	ll &ans = d[i][j][k]; vis[i][j][k] = kase; ans = 0;
	if (i == 2 * n - 1) {
		if (k == in[i][j]) return ans = 1;
		else return ans = 0;
	}
	for (int l = -1; l <= 1; l += 2)
		ans += dp(i + 1, j + l, k - in[i][j]);
	return ans;
}

void print(int i, int j, int k) {
	if (i >= 2 * n + 1) return;
	for (int l = -1; l <= 1; l += 2) {
		int ti = i + 1, tj = j + l, tk = k - in[i][j];
		if (pos[ti][tj] == kase &&vis[ti][tj][tk] == kase&& d[ti][tj][tk]) {
			if (l == -1) putchar('L');
			else putchar('R');
			print(ti, tj, tk);
			return;
		}
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &s) == 2 && n) {
		++kase; int l = 1, r = 2 * n - 1;
		For(i, 1, 2 * n - 1) {
			for (int j = l; j <= r; j += 2) {
				scanf("%d", in[i] + j);
				pos[i][j] = kase;
			}
			if (i < n) ++l, --r; else --l, ++r;
		}
		++l; --r;
		ll ans = 0; int idx = -1;
		for (int j = l; j <= r; j += 2) {
			ans += dp(1, j, s);
			if (ans&&idx == -1) idx = j;
		}
		printf("%lld\n", ans);
		if (ans) {
			printf("%d ",idx/2);
			print(1, idx, s);
			putchar('\n');
		}
		else puts("");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}