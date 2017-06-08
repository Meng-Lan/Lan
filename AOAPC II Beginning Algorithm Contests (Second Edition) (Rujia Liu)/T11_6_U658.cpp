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

const int maxn = 20;
const int maxm = 105;
const int INF = 1e9;
int n, m, cost[maxm], mark[1 << maxn], dist[1 << maxn];
char from[maxm][maxn + 5], to[maxm][maxn + 5];

struct Node {
	int bugs, dist;
	Node(int b = 0, int d = 0) :bugs(b), dist(d) {}
	bool operator<(const Node &t) const {
		return dist > t.dist;
	}
};

int solve() {
	FOR(i, 0, 1 << n) { mark[i] = 0; dist[i] = INF; }
	std::priority_queue<Node> q;
	Node start((1 << n) - 1, 0);
	q.push(start);
	dist[start.bugs] = 0;
	while (!q.empty()) {
		Node u = q.top(); q.pop();
		if (u.bugs == 0) return u.dist;
		if (mark[u.bugs]) continue;
		mark[u.bugs] = 1;
		FOR(i, 0, m) {
			bool patchable = true;
			FOR(j, 0, n) {
				if (from[i][j] == '-' && (u.bugs&(1 << j))) { patchable = false; break; }
				if (from[i][j] == '+' && !(u.bugs&(1 << j))) { patchable = false; break; }
			}
			if (!patchable) continue;
			Node u2(u.bugs, u.dist + cost[i]);
			FOR(j, 0, n) {
				if (to[i][j] == '-') u2.bugs &= ~(1 << j);
				if (to[i][j] == '+') u2.bugs |= (1 << j);
			}
			int &D = dist[u2.bugs];
			if (D < 0 || u2.dist < D) {
				D = u2.dist;
				q.push(u2);
			}
		}
	}
	return -1;
}


int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while(scanf("%d%d",&n,&m)==2&&n){
		FOR(i, 0, m) scanf("%d %s %s", cost + i, from + i, to + i);
		int ans = solve();
		printf("Product %d\n", ++kase);
		if (ans < 0) printf("Bugs cannot be fixed.\n\n");
		else printf("Fastest sequence takes %d seconds.\n\n", ans);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}