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
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 10010;
std::vector<int> G[maxn];
int vis[maxn], color[maxn], inq[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int n, m;
	while (scanf("%d%d", &n, &m) == 2 && n&&m) {
		for (auto &t : G) t.clear();
		int u, v;
		FOR(i, 0, m) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		int k = 0, No = 0;
		For(i, 1, n) if (G[i].size() > k) {
			k = G[i].size(); No = i;
		}
		k |= 1;
		printf("%d\n", k);
		memset(inq, 0, sizeof(inq));
		memset(color, 0, sizeof(color));
		std::queue<int> q; q.push(No); inq[No] = 1;
		while (!q.empty()) {
			u = q.front(); q.pop();
			memset(vis, 0, sizeof(int)*(n + 1));
			for (auto &t : G[u]) {
				if (color[t]) vis[color[t]] = 1;
				if (!inq[t]) {
					q.push(t); inq[t] = 1;
				}
			}
			For(i, 1, n) if (!vis[i]) {
				color[u] = i; break;
			}
		}
		For(i, 1, n) printf("%d\n", color[i]);
		putchar('\n');
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}