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

const int INF = 1e9;
const int maxn = 1e3 + 10;
char s[maxn];
int k, n, d[maxn][26];
std::vector<int> G[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d %s", &k, s);
		int len = strlen(s); n = len / k;
		FOR(i, 0, n) {
			std::set<char> sc; G[i].clear();
			FOR(j, i*k, (i + 1)*k) sc.insert(s[j]);
			for (auto &t : sc) G[i].push_back(t - 'a');
		}
		FOR(i, 0, n) {
			if (!i) {
				FOR(j, 0, 26) d[i][j] = INF;
				for (auto &t : G[i]) d[i][t] = G[i].size();
			}
			else {
				int M = INF;
				FOR(j, 0, 26) d[i][j] = INF;
				FOR(j, 0, 26) M = std::min(M, d[i - 1][j]);
				//printf("#%d %d\n", i, M);
				for (auto &t : G[i]) d[i][t] = M + G[i].size();
				for (auto &l : G[i]) for (auto &r : G[i])
					if (l != r || G[i].size() == 1) {
						//printf("#%d %c->%c ", i, l + 'a', r + 'a');
						d[i][r] = std::min((std::vector<int>::size_type)d[i][r], d[i - 1][l] + G[i].size() - 1);
						//printf("d[%d][%d]:%d L:%u R:%u\n", i, r, d[i][r], M + G[i].size(), d[i - 1][l] + G[i].size() - 1);
					}
			}
		}
		int ans = INF;
		FOR(i, 0, 26) ans = std::min(ans, d[n - 1][i]);
		printf("%d\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}