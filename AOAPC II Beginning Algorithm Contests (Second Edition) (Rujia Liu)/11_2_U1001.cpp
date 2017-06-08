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
typedef std::pair<double, int> P;
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

const int maxn = 105;
const int INF = 1e9;

long long sqr(int x) { return (long long)x*x; }

struct Point {
	int x, y, z, r;
	Point(int x = 0, int y = 0, int z = 0, int r = 0) :x(x), y(y), z(z), r(r) {}
	double count(const Point& t) {
		double s = sqrt(sqr(x - t.x) + sqr(y - t.y) + sqr(z - t.z));
		return (s - std::min(s, (double)r + t.r)) * 10;
	}
};

Point dot[maxn];
int cnt, n;

struct Edge {
	int from, to;
	double dist;
	Edge(int u = 0, int v = 0, double d = 0) :from(u), to(v), dist(d) {}
};

struct Dijkstra {
	int n, m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	bool done[maxn];
	double d[maxn];

	void init(int n) {
		this->n = n;
		For(i, 0, n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, double dist) {
		edges.push_back(Edge(from, to, dist));
		m = edges.size();
		G[from].push_back(m - 1);
	}

	void dijkstra(int s) {
		memset(done, 0, sizeof(done));
		For(i, 0, n) d[i] = INF;
		d[s] = 0;
		std::priority_queue<P, std::vector<P>, std::greater<P>> q;
		q.push(mp(d[s], s));
		while (!q.empty()) {
			P x = q.top(); q.pop();
			int u = x.second;
			if (done[u]) continue;
			done[u] = true;
			FOR(i, 0, G[u].size()) {
				Edge &e = edges[G[u][i]];
				if (d[e.to] > d[u] + e.dist) {
					d[e.to] = d[u] + e.dist;
					q.push(mp(d[e.to], e.to));
				}
			}
		}
	}
}lan;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1 && n != -1) {
		FOR(i, 0, n) {
			int x, y, z, r;
			scanf("%d%d%d%d", &x, &y, &z, &r);
			dot[i] = Point(x, y, z, r);
		}
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		dot[n] = Point(x, y, z, 0);
		scanf("%d%d%d", &x, &y, &z);
		dot[n + 1] = Point(x, y, z, 0);
		lan.init(n + 2);
		FOR(i, 0, n) FOR(j, 0, n) if (i != j) 
			lan.AddEdge(i, j, dot[i].count(dot[j]));
		FOR(i, 0, n) {
			lan.AddEdge(n, i, dot[n].count(dot[i]));
			lan.AddEdge(i, n + 1, dot[i].count(dot[n + 1]));
		}
		lan.AddEdge(n, n + 1, dot[n].count(dot[n + 1]));
		/*FOR(i, 0, lan.edges.size()) {
			Edge &e = lan.edges[i];
			printf("u:%d v:%d dist:%d\n", e.from, e.to, e.dist);
		}*/
		lan.dijkstra(n);
		printf("Cheese %d: Travel time = %.0f sec\n", ++kase, lan.d[n + 1]);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}