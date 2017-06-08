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
int n, c, d, cn, dn;
P C[maxn], D[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &n, &c, &d);
	cn = dn = 0;
	FOR(i, 0, n) {
		int b, p; char ch;
		scanf("%d%d %c", &b, &p, &ch);
		if (ch == 'C') C[cn++] = P(p, b);
		if (ch == 'D') D[dn++] = P(p, b);
	}
	int mc = 0, md = 0, fd = 0, fc = 0, ans = 0;
	FOR(i, 0, cn) if (C[i].first <= c) {
		fc = 1; mc = std::max(mc, C[i].second);
	}
	FOR(i, 0, dn) if (D[i].first <= d) {
		fd = 1; md = std::max(md, D[i].second);
	}
	if (fc&&fd) ans = mc + md;
	std::sort(C, C + cn);
	//FOR(i, 0, cn) printf("P:%d B:%d\n", C[i].first, C[i].second);
	int l = 0, fl = 0, ml = 0, nl = 0;
	for (int r = cn - 1; r > l; --r) {
		while (nl < r&&C[nl].first + C[r].first <= c) {
			fl = 1;
			if (C[nl].second > ml) {
				ml = C[nl].second; l = nl;
			}
			++nl;
		}
		if (fl&&C[l].first + C[r].first <= c) ans = std::max(ans, C[r].second + ml);
	}
	std::sort(D, D + dn);
	l = 0, fl = 0, ml = 0, nl = 0;
	for (int r = dn - 1; r > l; --r) {
		while (nl < r&&D[nl].first + D[r].first <= d) {
			fl = 1;
			if (D[nl].second > ml) {
				ml = D[nl].second; l = nl;
			}
			++nl;
		}
		if (fl&&D[l].first + D[r].first <= d) ans = std::max(ans, D[r].second + ml);
	}
	printf("%d\n", ans);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}