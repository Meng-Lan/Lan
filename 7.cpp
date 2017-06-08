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
//#define mp std::make_pair
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


#define inf 1e9
#define eps 1e-10
const int md = 772002;
#define N 1010
using namespace std;
bool mp[9][9], ok[9][9];
int cnt[N];
ll f[1010][100];
int n, m, mxn; ll ans = 0;
char st[110];
struct point {
	int x, y;
	point(int x = 0, int y = 0) :x(x), y(y) {}
} q[100];
int lx[8] = { 1,0,-1,0,1,1,-1,-1 }, ly[8] = { 0,1,0,-1,1,-1,1,-1 };
ll solve()
{
	int tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (mp[i][j]) q[tot++] = point(i, j);
	for (int S = 0; S<(1 << tot); S++)
	{
		cnt[S] = 0;
		memset(ok, 0, sizeof(ok));
		for (int e = 0; e<tot; e++)
		{
			if (!((S >> e) & 1))
			{
				int i = q[e].x, j = q[e].y;
				for (int k = 0; k <= 7; k++)
				{
					int x = i + lx[k], y = j + ly[k];
					if (x<1 || y<1 || x>n || y>m) continue;
					ok[x][y] = 1;
				}
			}
			else cnt[S]++;
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if ((!ok[i][j] && (!mp[i][j]))) cnt[S]++;
	}
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for (int i = 0; i <= mxn; i++)
	{
		for (int S = 0; S<(1 << tot); S++)
		{
			if (i && (cnt[S] - (i - 1))>0) f[S][i] = (f[S][i] + f[S][i - 1] * (cnt[S] - (i - 1)) % md) % md;
			if (f[S][i] == 0) continue;
			for (int j = 0; j<tot; j++)
			{
				if (!((S >> j) & 1)) f[S | (1 << j)][i + 1] = (f[S | (1 << j)][i + 1] + f[S][i]) % md;
			}
		}
	}
	return f[(1 << tot) - 1][mxn];
}
void outit()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++) printf("%d ", mp[i][j]);
		printf("\n");
	}
}
void dfs(int dep, int s)
{
	if (dep>mxn)
	{
		ll x = solve();
		if (s & 1) ans = (ans - x + md) % md; else ans = (ans + x) % md;
		return;
	}
	dfs(mxn + 1, s);
	for (int now = dep; now <= mxn; now++)
	{
		int i = (now - 1) / m + 1, j = (now - 1) % m + 1;
		if (!mp[i][j])
		{
			bool ok = 1;
			for (int k = 0; k <= 7; k++)
			{
				int x = i + lx[k], y = j + ly[k];
				if (x<1 || y<1 || x>n || y>m) continue; 
				if (mp[x][y]) { ok = 0; break; }
			}
			if (ok)
			{
				mp[i][j] = 1;
				dfs(now + 1, s + 1);
				mp[i][j] = 0;
			}
		}
	}
}

bool check()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (mp[i][j])
			{
				for (int k = 0; k <= 7; k++)
				{
					int x = i + lx[k], y = j + ly[k];
					if (mp[x][y])
					{
						return false;
					}
				}
			}
		}
}


int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		mxn = n*m;
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", st + 1);
			for (int j = 1; j <= m; j++) mp[i][j] = st[j] == 'X';
		}
		ans = 0;
		if (check())
			dfs(1, 0);
		printf("Case #%d: %I64d\n", ++kase, (ans + md) % md);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}