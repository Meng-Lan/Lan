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
const ll INF = 1e18;
int n, a[maxn], vis[maxn], vs[maxn];
ll sum[maxn][2], sub[maxn];
std::vector<int> fa[maxn];

void dp(int f){
	if (vis[f]) return;
	//printf("f:%d\n", f);
	vis[f] = 1;
	sub[f] = -INF;
	sum[f][1] += a[f];
	std::vector<ll> tmp;
	FOR(i, 0, fa[f].size()) {
		dp(fa[f][i]);
		sum[f][1] += sum[fa[f][i]][1];
		tmp.push_back(std::max(sum[fa[f][i]][1], sum[fa[f][i]][0]));
		sub[f] = std::max(sub[f], sub[fa[f][i]]);
		vs[f] |= vs[fa[f][i]];
		sum[f][0] = std::max(sum[fa[f][i]][0], sum[f][0]);
		sum[f][0] = std::max(sum[f][0], sum[fa[f][i]][1]);
	}
	if (tmp.size() >= 2) {
		std::sort(tmp.begin(), tmp.end());
		int sz = tmp.size();
		if (tmp[sz - 1] > 0 && tmp[sz - 2] > 0) {
			sub[f] = std::max(sub[f], tmp[sz - 1] + tmp[sz - 2]);
			vs[f] = 1;
		}
	}
	return;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	For(i, 1, n) scanf("%d", a + i);
	FOR(i, 1, n) {
		int u, v; scanf("%d%d", &u, &v);
		fa[u].push_back(v);
	}
	dp(1);
	if (sub[1] <=0||(!vs[1])) printf("Impossible\n");
	else cout << sub[1] << endl;


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}