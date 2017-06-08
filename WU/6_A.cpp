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

const int maxn = 505;
const int dx[] = { 0,-1,0,1 };
const int dy[] = { -1,0,1,0 };
int in[maxn][maxn], vis[maxn][maxn][4];
int n, m;
typedef std::pair<P, int> PI;
char s[maxn];

bool check(int x, int y) {
	return x >= 0 && x < n&&y >= 0 && y < m;
}

int bfs() {
	std::queue<PI> q;
	q.push(PI(P(0, 0), 0));
	while (!q.empty()) {
		PI u = q.front(); q.pop();
		int x = u.first.first, y = u.first.second;
		if (x == n - 1 && y == m - 1) return u.second;
		FOR(i, 0, 4) {
			int tx = x + dx[i] * in[x][y], ty = y + dy[i] * in[x][y];
			if (!vis[x][y][i] && check(tx, ty)) {
				vis[x][y][i] = 1;
				q.push(PI(P(tx, ty), u.second + 1));
			}
		}
	}
	return -1;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &m) == 2 && n&&m) {
		FOR(i, 0, n) {
			scanf(" %s", s);
			FOR(j, 0, m) in[i][j] = s[j] - '0';
		}
		memset(vis, 0, sizeof(vis));
		printf("%d\n", bfs());
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}