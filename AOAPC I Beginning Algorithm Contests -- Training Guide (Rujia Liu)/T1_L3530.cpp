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

const int maxn = 505;
int in[2][maxn][maxn], d[2][maxn][maxn], vis[2][maxn][maxn], kase, n, m;

int dp(int on,int i,int j) {
	if (i > n || j > m) return 0;
	if (vis[on][i][j] == kase) return d[on][i][j];
	int &ans = d[on][i][j]; vis[on][i][j] = kase;
	ans = 0;
	if (on)
		ans = std::max(dp(on, i + 1, j), dp(!on, i + 1, j)) + in[on][i][j];
	else
		ans = std::max(dp(on, i, j + 1), dp(!on, i, j + 1)) + in[on][i][j];
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &m) == 2 && n) {
		FOR(i, 0, 2) FOR(j, 0, n) FOR(k, 0, m) scanf("%d", in[i][j] + k);
		++kase;
		for (int i = n - 2; i >= 0; --i) FOR(j, 0, m) in[0][i][j] += in[0][i + 1][j];
		FOR(i, 0, n) for (int j = m - 2; j >= 0; --j) in[1][i][j] += in[1][i][j + 1];
		printf("%d\n", std::max(dp(0, 0, 0), dp(1, 0, 0)));
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}