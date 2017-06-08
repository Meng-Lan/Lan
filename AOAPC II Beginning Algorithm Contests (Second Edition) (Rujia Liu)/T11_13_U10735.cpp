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

const int maxv = 105;
const int maxe = 510;
const int INF = 1e9;

struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) :from(u), to(v), cap(c), flow(f) {}
	Edge() :Edge(0, 0, 0, 0) {}
};

struct EdmondsKarp {
	int n, m;
	std::vector<Edge> edges;
	std::vector<int> G[maxv];
	int a[maxv], p[maxv];

	void init(int n) {
		this->n = n;
		For(i, 0, n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap) {
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	int Maxflow(int s, int t) {
		int flow = 0;
		for (;;) {
			std::queue<int> q;
			q.push(s);
			memset(a, 0, sizeof(a));
			a[s] = INF;
			while (!q.empty()) {
				int x = q.front(); q.pop();
				FOR(i, 0, G[x].size()) {
					Edge &e = edges[G[x][i]];
					if (!a[e.to] && e.cap > e.flow) {
						p[e.to] = G[x][i];
						a[e.to] = std::min(a[x], e.cap - e.flow);
						q.push(e.to);
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
}lan;

int n, m, u[maxe], v[maxe], directed[maxe], diff[maxe], id[maxe];
std::vector<int> G[maxv], vis[maxv], path;

void euler(int u) {
	FOR(i, 0, G[u].size()) if (!vis[u][i]) {
		vis[u][i] = 1;
		euler(G[u][i]);
		path.push_back(G[u][i] + 1);
	}
}

void print_ans() {
	FOR(i, 0, n) { G[i].clear(); vis[i].clear(); }
	path.clear();
	FOR(i, 0, m) {
		if (directed[i]) { G[u[i]].push_back(v[i]); vis[u[i]].push_back(0); }
		else {
			if (lan.edges[id[i]].flow > 0) {
				G[v[i]].push_back(u[i]); vis[v[i]].push_back(0);
			}
			else {
				G[u[i]].push_back(v[i]); vis[u[i]].push_back(0);
			}
		}
	}
	euler(0);

	printf("1");
	for(int i=path.size()-1;i>=0;--i) printf(" %d", path[i]);
	putchar('\n');
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		lan.init(n + 2);
		memset(diff, 0, sizeof(diff));
		FOR(i, 0, m) {
			char s[9];
			scanf("%d%d%s", u + i, v + i, s);
			--u[i]; --v[i]; ++diff[u[i]]; --diff[v[i]];
			directed[i] = (s[0] == 'D' ? 1 : 0);
			if (!directed[i]) {
				id[i] = lan.edges.size();
				lan.AddEdge(u[i], v[i], 1);
			}
		}
		bool ok = true;
		FOR(i, 0, n) if (diff[i] % 2) { ok = false; break; }
		int s = n, t = n + 1;

		if (ok) {
			int sum = 0;
			FOR(i, 0, n) {
				if (diff[i] > 0) { lan.AddEdge(s, i, diff[i] / 2); sum += diff[i] / 2; }
				if (diff[i] < 0) lan.AddEdge(i, t, -diff[i] / 2);
			}
			if (lan.Maxflow(s, t) != sum) ok = false;
		}

		if (!ok) printf("No euler circuit exist\n");
		else print_ans();
		if (T) putchar('\n');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}