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
const int maxn = 105;

struct Edge {
	int from, to, dist;
	Edge(int u, int v, int d) :from(u), to(v), dist(d) {}
	Edge() :Edge(0, 0, 0) {}
};

struct Dijkstra {
	int n, m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	bool done[maxn];
	int d[maxn], p[maxn];

	void init(int n) {
		this->n = n;
		FOR(i, 0, n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int dist) {
		edges.push_back(Edge(from, to, dist));
		edges.push_back(Edge(to, from, dist));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	void dijkstra(int s) {
		std::priority_queue<P,std::vector<P>,std::greater<P>> q;
		FOR(i, 0, n) d[i] = INF;
		d[s] = 0;
		memset(done, 0, sizeof(done));
		q.push(P(0, s));
		while (!q.empty()) {
			P x = q.top(); q.pop();
			int u = x.second;
			if (done[u]) continue;
			done[u] = true;
			FOR(i, 0, G[u].size()) {
				Edge &e = edges[G[u][i]];
				if (d[e.to] > d[u] + e.dist) {
					d[e.to] = d[u] + e.dist;
					p[e.to] = G[u][i];
					q.push(P(d[e.to], e.to));
				}
			}
		}
	}

	void print(int s, int t) {
		for (int u = t; u != s; u = edges[p[u]].from)
			printf("%d  ", u);
		printf("%d\n", s);
	}
}lan;

std::vector<int> G[10];
int n, t, Time[10];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &t) == 2) {
		lan.init(100); FOR(i, 0, n) G[i].clear();
		FOR(i, 0, n) scanf("%d", Time + i);
		std::string s;
		getline(cin, s);
		FOR(i, 0, n) {
			std::getline(cin, s);
			std::stringstream ss(s);
			int tmp;
			while (ss >> tmp) G[i].push_back(tmp);
		}
		if (t == 0) { puts("0"); continue; }
		FOR(i, 0, n) FOR(j, 0, G[i].size()) FOR(k, j + 1, G[i].size()) lan.AddEdge(G[i][j], G[i][k], (G[i][k] - G[i][j])*Time[i] + 60);
		//for (auto &t : lan.edges) printf("u:%d v:%d dist:%d\n",t.from,t.to,t.dist);
		lan.dijkstra(0);
		if (lan.d[t] != INF) printf("%d\n", lan.d[t] - 60);
		else puts("IMPOSSIBLE");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}