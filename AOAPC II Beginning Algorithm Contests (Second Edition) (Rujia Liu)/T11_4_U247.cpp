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

const int maxn = 30;
std::vector<std::string> name;
std::map<std::string, int> msi;
int n, m, d[maxn][maxn], vis[maxn];

int ID(const std::string &t) {
	if (msi.find(t) != msi.end()) return msi[t];
	name.push_back(t);
	return msi[t] = name.size() - 1;
}

void dfs(int u) {
	vis[u] = 1;
	FOR(v, 0, n) if (!vis[v] && d[u][v] && d[v][u]) {
		printf(", %s", name[v].c_str());
		dfs(v);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d%d", &n, &m) == 2 && n) {
		std::string s, t;
		name.clear(); msi.clear();
		memset(d, 0, sizeof(d));
		FOR(i, 0, n) d[i][i] = 1;
		FOR(i, 0, m) {
			cin >> s >> t;
			int is = ID(s), it = ID(t);
			d[is][it] = 1;
		}
		FOR(k, 0, n) FOR(i, 0, n) FOR(j, 0, n) d[i][j] |= d[i][k] && d[k][j];
		if (kase > 0) putchar('\n');
		printf("Calling circles for data set %d:\n", ++kase);
		memset(vis, 0, sizeof(vis));
		FOR(i, 0, n) if (!vis[i]) {
			printf("%s", name[i].c_str());
			dfs(i); putchar('\n');
		}
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}