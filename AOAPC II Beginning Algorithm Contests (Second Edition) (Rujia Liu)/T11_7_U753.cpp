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

const int maxn = 405;
const int INF = 1e8;
int n, m, k, cnt, target[maxn], device[maxn], d[maxn][maxn];
std::map<std::string, int> id;

int ID(const std::string s) {
	if (id.find(s) != id.end()) return id[s];
	return id[s] = cnt++;
}

struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) :from(u), to(v), cap(c), flow(f) {}
	Edge() :Edge(0, 0, 0, 0) {}
};

struct EdmondsKarp {
	int n, m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	int a[maxn];
	int p[maxn];

	void init() {
		FOR(i, 0, n) G[i].clear();
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
			memset(a, 0, sizeof(a));
			std::queue<int> Q;
			Q.push(s);
			a[s] = INF;
			while (!Q.empty()) {
				int x = Q.front(); Q.pop();
				FOR(i, 0, G[x].size()) {
					Edge& e = edges[G[x][i]];
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
};

EdmondsKarp lan;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		std::string s1, s2; id.clear(); cnt = 0;
		scanf("%d", &n);
		FOR(i, 0, n) {
			cin >> s1; target[i] = ID(s1);
		}
		scanf("%d", &m);
		FOR(i, 0, m) {
			cin >> s1 >> s2;
			device[i] = ID(s2);
		}
		scanf("%d", &k);
		memset(d, 0, sizeof(d));
		FOR(i, 0, k) {
			cin >> s1 >> s2;
			d[ID(s1)][ID(s2)] = 1;
		}

		FOR(k, 0, cnt) FOR(i, 0, cnt) FOR(j, 0, cnt) d[i][j] = d[i][j] || d[i][k] && d[k][j];

		lan.n = cnt + 2; lan.init();
		FOR(i, 0, n) lan.AddEdge(target[i], cnt + 1, 1);
		FOR(i, 0, m) lan.AddEdge(cnt, device[i], 1);

		FOR(i, 0, m) FOR(j, 0, n) if (d[device[i]][target[j]]) lan.AddEdge(device[i], target[j], INF);
		printf("%d\n", m - lan.Maxflow(cnt, cnt + 1));
		if (T) putchar('\n');
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}