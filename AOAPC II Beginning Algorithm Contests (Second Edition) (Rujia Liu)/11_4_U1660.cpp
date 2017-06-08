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

const int maxn = 110;
const int INF = 1e8;


struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) :from(u), to(v), cap(c), flow(f) {}
};

struct EK {
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	int p[maxn], a[maxn];
	int n, m;

	void init(int n) {
		this->n = n;
		FOR(i, 0, n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int u, int v, int c) {
		edges.push_back(Edge(u, v, c, 0));
		edges.push_back(Edge(v, u, 0, 0));
		m = edges.size();
		G[u].push_back(m - 2);
		G[v].push_back(m - 1);
	}

	int maxflow(int s, int t) {
		int flow = 0;
		for (;;) {
			memset(a, 0, sizeof(a));
			std::queue<int> Q;
			Q.push(s);
			a[s] = INF;
			while (!Q.empty()) {
				int x = Q.front(); Q.pop();
				FOR(i, 0, G[x].size()) {
					Edge &e = edges[G[x][i]];
					if (!a[e.to] && e.cap > e.flow) {
						p[e.to] = G[x][i];
						a[e.to] = std::min(a[x], e.cap - e.flow);
						Q.push(e.to);
					}
				}
				if (a[t]) break;
			}
			if (!a[t]) break;
			for (int u = t; u != s; u = edges[p[u]].from) {
				edges[p[u]].flow += a[t];
				edges[p[u] ^ 1].flow -= a[t];
			}
			flow += a[t];
		}
		return flow;
	}
}in;

int n, m;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &m) == 2) {
		int ans = INF;
		in.init(n * 2);
		FOR(i, 0, m) {
			int u, v;
			scanf(" (%d,%d)", &u, &v);
			in.AddEdge(u + n, v, INF);
			in.AddEdge(v + n, u, INF);
		}
		in.AddEdge(0, n, INF);
		FOR(t, 1, n) {
			EK deal = in;
			FOR(i, 1, n) if (i == t) deal.AddEdge(t, t + n, INF);
			else deal.AddEdge(i, i + n, 1);
			ans = std::min(ans, deal.maxflow(0, t));
		}
		if (ans >= n) ans = n;
		printf("%d\n", ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}