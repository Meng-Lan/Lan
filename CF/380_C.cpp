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

const int INF = 2e9;
const int maxn = 2e5 + 10;
int n, k, s, t, g[maxn], c[maxn], v[maxn], d[maxn];

bool check(int ans) {
	if (ans < d[k - 1]) return false;
	int tme = 0;
	FOR(i, 0, k) {
		if (ans >= (d[i] << 1)) tme += d[i];
		else tme += 3 * d[i] - ans;
	}
	return tme <= t;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d%d", &n, &k, &s, &t);
	FOR(i, 0, n) scanf("%d%d", c + i, v + i);
	FOR(i, 0, k) scanf("%d", g + i);
	g[k++] = 0;
	std::sort(g, g + k);
	if (g[k] != s) g[k++] = s;
	--k;
	FOR(i, 0, k) d[i] = g[i + 1] - g[i];
	std::sort(d, d + k);
	//FOR(i, 0, k) cout <<"# "<< d[i] << endl;
	int l = 0, r = INF;
	while (l < r) {
		int m = l + (r - l) / 2;
		if (check(m)) r = m;
		else l = m + 1;
	}
	int ans = INF;
	FOR(i, 0, n) if (v[i] >= l) ans = std::min(ans, c[i]);
	if (ans != INF)
		cout << ans << '\n';
	else cout << -1 << '\n';


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}