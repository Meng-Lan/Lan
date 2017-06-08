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

const int INF = 1e8;
const int maxn = 2005;
int n, e;

struct Edge {
	int from, to, cap, flow, cost;
	Edge(int u, int v, int c, int f, int w) :from(u), to(v), cap(c), flow(f), cost(w) {}
	Edge() :Edge(0, 0, 0, 0, 0) {}
};

struct MCMF {
	int n, m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	int inq[maxn];
	int d[maxn];
	int p[maxn];
	int a[maxn];

	void init() {
		FOR(i, 0, n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap, int cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool BellmanFord(int s, int t, const int maxflow, int &flow, long long &cost) {
		FOR(i, 0, n) d[i] = INF;
		memset(inq, 0, sizeof(inq));
		d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

		std::queue<int> Q;
		Q.push(s);
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			inq[u] = 0;
			FOR(i, 0, G[u].size()) {
				Edge& e = edges[G[u][i]];
				if (e.cap > e.flow&&d[e.to] > d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					p[e.to] = G[u][i];
					a[e.to] = std::min(a[u], e.cap - e.flow);
					if (!inq[e.to]) {
						Q.push(e.to); inq[e.to] = 1;
					}
				}
			}
		}
		if (d[t] == INF) return false;
		if (flow + a[t] > maxflow) a[t] = maxflow - flow;
		flow += a[t];
		cost += d[t] * a[t];
		for (int u = t; u != s; u = edges[p[u]].from) {
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
		}
		return true;
	}

	int MincostMaxflow(int s, int t, const int maxflow, long long &cost) {
		int flow = 0; cost = 0;
		while (flow < maxflow&&BellmanFord(s, t, maxflow, flow, cost));
		return flow;
	}
};

MCMF lan;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &e) == 2) {
		lan.n = 2 * n - 2; lan.init();
		FOR(i, 2, n) lan.AddEdge(i - 1, i + n - 2, 1, 0);
		FOR(i, 0, e) {
			int u, v, cost;
			scanf("%d%d%d", &u, &v, &cost);
			if (u != 1 && u != n) u += n - 2;
			else --u;
			--v;
			lan.AddEdge(u, v, 1, cost);
		}
		ll cost = 0;
		lan.MincostMaxflow(0, n - 1, 2, cost);
		printf("%lld\n", cost);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}