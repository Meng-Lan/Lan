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

const int maxn = 100010;
const ll INF = 1e18;
int n, in[maxn], vis[maxn][2];
ll d[maxn][2];
ll ans;
char t[maxn];
std::string s[maxn][2];


ll dp(int cur, int type) {
	if (cur == n - 1) return type == 0 ? 0 : in[cur];
	ll &ans = d[cur][type];
	if (vis[cur][type]) return ans;
	vis[cur][type] = 1;
	ll tmp1 = INF, tmp2 = INF;
	if (s[cur][type] <= s[cur + 1][0]) tmp1 = dp(cur + 1, 0);
	if (s[cur][type] <= s[cur + 1][1]) tmp2 = dp(cur + 1, 1);
	if (type == 0) return ans = std::min(tmp1, tmp2);
	else return ans = std::min(tmp1, tmp2) + in[cur];
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	FOR(i, 0, n) scanf("%d", in + i);
	FOR(i, 0, n) {
		scanf(" %s", t);
		int len = strlen(t);
		s[i][0].assign(t, t + len);
		s[i][1] = s[i][0];
		std::reverse(s[i][1].begin(), s[i][1].end());
	}
	ll ans = std::min(dp(0, 0), dp(0, 1));
	if (ans >= INF) printf("-1\n");
	else printf("%I64d\n", ans);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}