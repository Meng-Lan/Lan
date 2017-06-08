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

const int maxn = 1010;
const int INF = 1e9;
struct Lan {
	int x, c, d;
	Lan(int x, int c, int d) :x(x), c(c), d(d) {}
	Lan() = default;
	bool operator<(const Lan &t)const { return x < t.x; }
}in[maxn];
int n, kase, vis[maxn][maxn][2];
double v, x, sum[maxn];
double d[maxn][maxn][2];

double cost(double x1, double x2, int i, int j) {
	double finished_dt = 0;
	assert(i <= j);
	if (i >= 0 && j >= 0) finished_dt += sum[j] - sum[i - 1];
	return (sum[n] - finished_dt) * fabs(x2 - x1) / v;
}

double dp(int i, int j, int p) {
	if (i == 1 && j == n) return 0.0;
	double &ans = d[i][j][p];
	if (vis[i][j][p] == kase) return ans;
	vis[i][j][p] = kase;
	ans = INF;
	double tx = (p ? in[j].x : in[i].x);
	if (i > 1) ans = std::min(ans, dp(i - 1, j, 0) + cost(tx, in[i - 1].x, i, j));
	if (j < n) ans = std::min(ans, dp(i, j + 1, 1) + cost(tx, in[j + 1].x, i, j));
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%lf%lf", &n, &v, &x) == 3 && n) {
		double sumc = 0.0; ++kase;
		For(i, 1, n) scanf("%d%d%d", &in[i].x, &in[i].c, &in[i].d), sumc += in[i].c;
		std::sort(in + 1, in + 1 + n); sum[0] = 0.0;
		For(i, 1, n) sum[i] = sum[i - 1] + in[i].d;
		in[0].x = -INF; in[n + 1].x = INF;
		double ans = INF;
		For(i, 1, n+1)
			if (x > in[i - 1].x&&x < in[i].x) {
				if (i > 1) ans = std::min(ans, dp(i - 1, i - 1, 0) + cost(x, in[i - 1].x, -1, -1));
				if (i <= n) ans = std::min(ans, dp(i, i, 0) + cost(x, in[i].x, -1, -1));
				break;
			}
		printf("%.0f\n", floor(ans + sumc));
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}