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
std::vector<int> Eratosthenes(const int len,int *vis) {
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

int dice24[24][6] = {
	{ 2,1,5,0,4,3 },
	{ 2,0,1,4,5,3 },
	{ 2,4,0,5,1,3 },
	{ 2,5,4,1,0,3 },
	{ 4,2,5,0,3,1 },
	{ 5,2,1,4,3,0 },
	{ 1,2,0,5,3,4 },
	{ 0,2,4,1,3,5 },
	{ 0,1,2,3,4,5 },
	{ 4,0,2,3,5,1 },
	{ 5,4,2,3,1,0 },
	{ 1,5,2,3,0,4 },
	{ 5,1,3,2,4,0 },
	{ 1,0,3,2,5,4 },
	{ 0,4,3,2,1,5 },
	{ 4,5,3,2,0,1 },
	{ 1,3,5,0,2,4 },
	{ 0,3,1,4,2,5 },
	{ 4,3,0,5,2,1 },
	{ 5,3,4,1,2,0 },
	{ 3,4,5,0,1,2 },
	{ 3,5,1,4,0,2 },
	{ 3,1,0,5,4,2 },
	{ 3,0,4,1,5,2 }
};
const int maxn = 4;
int color[maxn][6],in[maxn][6];
int n, ans, r[maxn];

std::vector<std::string> names;
int ID(std::string s) {
	int n = names.size();
	FOR(i, 0, names.size()) if (names[i] == s) return i;
	names.push_back(s);
	return n;
}

void check() {
	FOR(i, 0, n) FOR(j, 0, 6) color[i][dice24[r[i]][j]] = in[i][j];
	int tot = 0;
	FOR(j, 0, 6) {
		int cnt[maxn * 6];
		memset(cnt, 0, sizeof(cnt));
		int maxface = 0;
		FOR(i, 0, n)
			maxface = std::max(maxface, ++cnt[color[i][j]]);
		tot += n - maxface;
	}
	ans = std::min(ans, tot);
}

void dfs(int d) {
	if (d == n) check();
	else FOR(i, 0, 24) {
		r[d] = i;
		dfs(d + 1);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		std::string s;
		names.clear();
		FOR(i, 0, n) FOR(j, 0, 6) {
			cin >> s;
			in[i][j] = ID(s);
		}
		ans = n * 6;
		r[0] = 0;
		dfs(1);
		printf("%d\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}