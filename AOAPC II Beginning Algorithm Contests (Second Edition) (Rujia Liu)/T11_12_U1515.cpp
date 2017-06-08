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

int h, w, d, f, b;
const int maxn = 50*50+10;
const int INF = 1e9;
char s[90][90];

struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) :from(u), to(v), cap(c), flow(f) {}
	Edge() :Edge(0, 0, 0, 0) {}
};

bool operator < (const Edge& a, const Edge& b) {
	return a.from < b.from || (a.from == b.from && a.to < b.to);
}

struct Dinic {
	int n, m, s, t;
	std::vector<Edge> edges;    // 边数的两倍
	std::vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
	bool vis[maxn];        // BFS使用
	int d[maxn];           // 从起点到i的距离
	int cur[maxn];         // 当前弧指针

	void init(int n) {
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap) {
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool BFS() {
		memset(vis, 0, sizeof(vis));
		std::queue<int> Q;
		Q.push(s);
		vis[s] = 1;
		d[s] = 0;
		while (!Q.empty()) {
			int x = Q.front(); Q.pop();
			for (int i = 0; i < G[x].size(); i++) {
				Edge& e = edges[G[x][i]];
				if (!vis[e.to] && e.cap > e.flow) {
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int DFS(int x, int a) {
		if (x == t || a == 0) return a;
		int flow = 0, f;
		for (int& i = cur[x]; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (d[x] + 1 == d[e.to] && (f = DFS(e.to, std::min(a, e.cap - e.flow))) > 0) {
				e.flow += f;
				edges[G[x][i] ^ 1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		return flow;
	}

	int Maxflow(int s, int t) {
		this->s = s; this->t = t;
		int flow = 0;
		while (BFS()) {
			memset(cur, 0, sizeof(cur));
			flow += DFS(s, INF);
		}
		return flow;
	}
}lan;

inline int ID(int a, int b) { return a*w + b; }

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d", &w, &h, &d, &f, &b);
		FOR(i, 0, h) scanf(" %s", s[i]);
		int cost = 0;
		FOR(i, 0, h) {
			if (s[i][0] == '.') {
				s[i][0] = '#'; cost += f;
			}
			if (s[i][w - 1] == '.') {
				s[i][w - 1] = '#'; cost += f;
			}
		}
		FOR(i, 0, w) {
			if (s[0][i] == '.') {
				s[0][i] = '#'; cost += f;
			}
			if (s[h - 1][i] == '.') {
				s[h - 1][i] = '#'; cost += f;
			}
		}

		lan.init(h*w + 2);

		FOR(i, 0, h) FOR(j, 0, w) {
			if (s[i][j] == '#') {
				int cap = INF;
				if (i != 0 && i != h - 1 && j != 0 && j != w - 1) cap = d;
				lan.AddEdge(h*w, ID(i, j), cap);
			}
			else lan.AddEdge(ID(i, j), h*w + 1, f);

			if (i > 0) lan.AddEdge(ID(i, j), ID(i - 1, j), b);
			if (i < h - 1) lan.AddEdge(ID(i, j), ID(i + 1, j), b);
			if (j > 0) lan.AddEdge(ID(i, j), ID(i, j - 1), b);
			if (j < w - 1) lan.AddEdge(ID(i, j), ID(i, j + 1), b);
		}

		printf("%d\n", cost + lan.Maxflow(h*w, h*w + 1));
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}