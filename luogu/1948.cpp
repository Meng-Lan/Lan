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

const int maxn = 1000 + 10;
struct Edge {
	int from, to, val;
	Edge(int u, int v, int cost) :from(u), to(v), val(cost) {}
	Edge() :Edge(0, 0, 0) {}
};
std::vector<Edge> edges;
std::vector<int> G[maxn];
int n, p, k, vis[maxn];

int bfs() {
	std::queue < P> q; q.push(P(1, 0));
	while (!q.empty()) {
		P u = q.front(); q.pop();
		if (u.first == n) return u.second;
		for (auto &t : G[u.first]) if (!vis[t]) {
			Edge &e = edges[t];
			int to = e.from == u.first ? e.to : e.from;
			q.push(P(to, u.second + 1)); vis[t] = 1;
		}
	}
	return -1;
}

const int maxm = 1e5 + 10;
const int INF = 1e9;
bool inq[maxm];
int cnt[maxm], d[maxm];

int BellmanFord(int s,int mid) {
	std::queue<int> q;
	for (auto &t : d) t = INF; memset(inq, 0, sizeof(inq)); memset(cnt, 0, sizeof(cnt));
	d[s] = 0; inq[s] = true; q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u==n&&d[n]<=k) return true;
		inq[u] = false;
		for (auto &t : G[u]) {
			Edge &e = edges[t];
			int to = e.from == u ? e.to : e.from;
			if (d[u] < INF&&d[to] > d[u]+(e.val>=mid)) {
				d[to] = d[u] + (e.val >= mid);
				if (!inq[to]) {
					q.push(to); inq[to] = true; if (++cnt[to] > n) return false;
				}
			}
		}
	}
	return false;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &n, &p, &k);
	FOR(i, 0, p) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		edges.push_back(Edge(u, v, c));
		G[u].push_back(edges.size() - 1);
		G[v].push_back(edges.size() - 1);
	}
	int step = bfs();
	if (step == -1) { puts("-1"); return 0; }
	assert(step != -1);
	if (step <= k) puts("0");
	else {
		int l = 0, r = 1e6 + 10;
		while (l < r) {
			int m = l + (r - l) / 2;
			if (BellmanFord(1, m)) r = m;
			else l = m + 1;
		}
		printf("%d\n", l - 1);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}