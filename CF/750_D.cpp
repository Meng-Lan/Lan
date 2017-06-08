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

const int maxn = 100;
const int sta = 8;
const int dx[] = { -1,-1,0,1,1,1,0,-1 };
const int dy[] = { 0,-1,-1,-1,0,1,1,1 };
int vis[maxn][maxn][sta], G[maxn][maxn];
int n, t[maxn];

struct Point{
	int x, y, dir, num;
	Point(int x, int y, int d, int n) :x(x), y(y), dir(d), num(n) {}
};

void run(Point t, int step) {
	For(i, 1, step) {
		int tx = i*dx[t.dir], ty = i*dy[t.dir];
		G[t.x + tx][t.y + ty] = 1;
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	FOR(i, 0, n) scanf("%d", t + i);
	std::queue<Point> q;
	q.push(Point(40, 40, 6, 0));
	while (!q.empty()) {
		Point tmp = q.front(); q.pop();
		if (vis[tmp.x][tmp.y][tmp.dir] || tmp.num >= n) continue;
		vis[tmp.x][tmp.y][tmp.dir] = 1;
		run(tmp, t[tmp.num]);
		int dir1 = (tmp.dir + 1) % 8, dir2 = (tmp.dir - 1 + 8) % 8;
		q.push(Point(tmp.x + dx[tmp.dir] * t[tmp.num], tmp.y + dy[tmp.dir] * t[tmp.num], dir1, tmp.num + 1));
		q.push(Point(tmp.x + dx[tmp.dir] * t[tmp.num], tmp.y + dy[tmp.dir] * t[tmp.num], dir2, tmp.num + 1));
	}
	int cnt = 0;
	FOR(i, 0, maxn) FOR(j, 0, maxn) if (G[i][j]) ++cnt;
	cout << cnt << endl;

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}