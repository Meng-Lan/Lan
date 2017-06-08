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
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 105;
int in[maxn][maxn],d[maxn][maxn], vis[maxn][maxn];
int kase, r, c;
char s[maxn];

const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };

bool check(int x, int y) {
	return x >= 0 && x < r&&y >= 0 && y < c;
}

int dp(int r0, int c0) {
	int &ans = d[r0][c0];
	if (vis[r0][c0] == kase) return ans;
	vis[r0][c0] = kase; ans = 1;
	FOR(i, 0, 4) {
		int x = r0 + dx[i], y = c0 + dy[i];
		if (check(x, y) && in[x][y]>in[r0][c0]) ans = std::max(ans, dp(x, y) + 1);
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (scanf(" %s%d%d", s, &r, &c) == 3) {
		FOR(i, 0, r) FOR(j, 0, c) scanf("%d", in[i] + j);
		printf("%s: ", s); kase++;
		int ans = 0;
		FOR(i, 0, r) FOR(j, 0, c) ans = std::max(ans, dp(i, j));
		printf("%d\n", ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}