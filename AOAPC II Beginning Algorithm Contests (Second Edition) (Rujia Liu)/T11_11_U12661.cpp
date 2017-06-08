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

const int maxn = 305;
const int maxm = 5e4 + 10;
const int INF = 1e9;

struct Edge {
	int from, to, a, b, t;
	Edge(int u, int v, int a, int b, int t) :from(u), to(v), a(a), b(b), t(t) {}
	Edge() :Edge(0, 0, 0, 0, 0) {}
};

struct Dijkstra {
	int n, m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	bool done[maxn];
	int d[maxn], p[maxn];

	void init(int n) {
		this->n = n;
		For(i, 0, n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int u, int v, int a, int b, int t) {
		if (t > a) return;
		edges.push_back(Edge(u, v, a, b, t));
		m = edges.size();
		G[u].push_back(m - 1);
	}

	void dijkstra(int s) {
		std::priority_queue<P,std::vector<P>,std::greater<P>> Q;
		memset(done, 0, sizeof(done));
		For(i, 0, n) d[i] = INF;
		d[s] = 0;
		Q.push(mp(0, s));
		while (!Q.empty()) {
			P x = Q.top(); Q.pop();
			int u = x.second;
			if (done[u]) continue;
			done[u] = true;
			//printf("u:%d\n", u);
			FOR(i, 0, G[u].size()) {
				Edge &e = edges[G[u][i]];
				int bg = d[u] % (e.a + e.b), ed = bg + e.t;
				//printf("e:%d bg:%d ed:%d\n", G[u][i], bg, ed);
				if (bg > e.a || ed > e.a) {
					int t = d[u] + e.a + e.b - bg + e.t;
					if (d[e.to] > t) {
						d[e.to] = t;
						p[e.to] = G[u][i];
						Q.push(mp(t, e.to));
					}
				}
				else {
					if (d[e.to] > d[u] + e.t) {
						d[e.to] = d[u] + e.t;
						p[e.to] = G[u][i];
						Q.push(mp(d[e.to], e.to));
					}
				}
			}
		}
	}
}lan;

int n, m, s, t;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d%d%d%d", &n, &m, &s, &t) == 4) {
		lan.init(n);
		FOR(i, 0, m) {
			int u, v, a, b, t;
			scanf("%d%d%d%d%d", &u, &v, &a, &b, &t);
			lan.AddEdge(u, v, a, b, t);
		}
		lan.dijkstra(s);
		printf("Case %d: %d\n", ++kase, lan.d[t]);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}