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

const int maxn = 1005;
const int maxq = 8;
int n, q, x[maxn], y[maxn], cost[maxq], p[maxn];
std::vector<int> pack[maxq];
struct Edge {
	int form, to, cost;
	Edge(int u, int v, int c) :form(u), to(v), cost(c) {}
	Edge() :Edge(0, 0, 0) {}
	bool operator<(const Edge &t) const {
		return cost < t.cost;
	}
};

int find(int X) {
	return X == p[X] ? X : p[X] = find(p[X]);
}

int kruskal(const std::vector<Edge> &edge,std::vector<Edge> &t,int cnt) {
	if (cnt == 1) return 0; 
	int ans = 0,m=edge.size();
	t.clear();
	FOR(i, 0, m) {
		int x = find(edge[i].form), y = find(edge[i].to), c = edge[i].cost;
		if (x != y) {
			t.emplace_back(edge[i]); ans += c;p[x] = y;
			if (--cnt == 0) break;
		}
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		FOR(i, 0, q) {
			int num; scanf("%d%d", &num, cost + i);
			pack[i].clear();
			FOR(j, 0, num) {
				int t; scanf("%d", &t); pack[i].push_back(t - 1);
			}
		}
		FOR(i, 0, n) scanf("%d%d", x + i, y + i);
		std::vector<Edge> edge, tmp;
		edge.reserve(n*(n + 1) / 2); tmp.reserve(n);
		FOR(i, 0, n) FOR(j, i + 1, n)
			edge.emplace_back(i, j, (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]));
		std::sort(edge.begin(), edge.end());
		FOR(i, 0, n) p[i] = i;
		int ans = kruskal(edge, tmp, n);
		FOR(s, 0, (1 << q)) {
			FOR(i, 0, n) p[i] = i;
			int cnt = n, c = 0;
			FOR(i, 0, q) if (s&(1 << i)) {
				c += cost[i];
				FOR(j, 1, pack[i].size()) {
					int u = find(pack[i][j]), v = find(pack[i][0]);
					if (u != v) {
						p[u] = v; --cnt;
					}
				}
			}
			std::vector<Edge> dummy;
			ans = std::min(ans, c + kruskal(tmp, dummy, cnt));
		}
		printf("%d\n", ans);
		if (T) printf("\n");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}