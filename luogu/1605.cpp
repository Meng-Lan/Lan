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
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 10;
int G[maxn][maxn], n, m, t, bx, by, ex, ey, cnt, vis[maxn][maxn];

inline bool check(int x, int y) {
	return x >= 1 && x <= n&&y >= 1 && y <= m&&!G[x][y] && !vis[x][y];
}

const int dx[] = { -1,0,1,0 };
const int dy[] = { 0,-1,0,1 };

void dfs(int x, int y) {
	if (x == ex&&y == ey) { ++cnt; return; }
	FOR(i, 0, 4) if (check(x + dx[i], y + dy[i])) {
		vis[x + dx[i]][y + dy[i]] = 1; dfs(x + dx[i], y + dy[i]); vis[x + dx[i]][y + dy[i]] = 0;
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d%d%d%d%d", &n, &m, &t, &bx, &by, &ex, &ey);
	FOR(i, 0, t) { int x, y; scanf("%d%d", &x, &y); G[x][y] = 1; }
	vis[bx][by] = 1;
	dfs(bx, by);
	printf("%d\n", cnt);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}