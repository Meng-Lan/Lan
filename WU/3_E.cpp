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

const int maxn = 3000 + 10;
const int dx[] = { 1,1,1,0,-1,-1,-1,0 };
const int dy[] = { 1,0,-1,-1,-1,0,1,1 };
int r, c, n, ans;
int id[maxn][maxn * 2], g[maxn][maxn * 2], fa[maxn*maxn * 2], rk[maxn*maxn * 2];
typedef std::pair<int&, int> p;
std::stack<p> s;

void init(int len) {
	FOR(i, 0, len) fa[i] = i, rk[i] = 0;
}

int find(int x) {
	while (x != fa[x]) x = fa[x];
	return x;
}

void Union(int x, int y, int on) {
	x = find(x), y = find(y);
	if (x == y) return;
	if (rk[x] <= rk[y]) {
		if (on) s.push(p(fa[x], fa[x]));
		fa[x] = y;
		if (rk[x] == rk[y]) {
			if (on) s.push(p(rk[y], rk[y]));
			rk[y]++;
		}
	}
	else {
		if (on) s.push(p(fa[y], fa[y]));
		fa[y] = x;
	}
}

void rollback(int on) {
	while (!s.empty()) {
		if (on) s.top().first = s.top().second;
		s.pop();
	}
}

void Add(int x, int y,int on) {
	FOR(i, 0, 8) {
		int tx = x + dx[i], ty = y + dy[i];
		if (ty < 1) ty += 2 * c;
		if (ty > 2 * c) ty -= 2 * c;
		if (tx >= 1 && tx <= r&&g[tx][ty])
			Union(id[x][y], id[tx][ty], on);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &r, &c, &n);
	for (int i = 1, t = 0; i <= r; ++i) For(j, 1, 2 * c) id[i][j] = t++;
	init(r*c * 2);
	FOR(i, 0, n) {
		int x, y;
		scanf("%d%d", &x, &y);
		g[x][y] = g[x][y + c] = 1;
		Add(x, y, 1);
		Add(x, y + c, 1);
		if (find(id[x][y]) == find(id[x][y + c])) {
			rollback(1);
			g[x][y] = g[x][y + c] = 0;
		}
		else {
			rollback(0);
			++ans;
		}
	}
	cout << ans << endl;


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}