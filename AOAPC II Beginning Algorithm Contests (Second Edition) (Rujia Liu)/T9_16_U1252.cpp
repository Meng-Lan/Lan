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
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 128;
const int maxm = 11;
char str[maxn];
int d[1 << maxm][1 << maxm], vis[1<<maxm][1<<maxm];
int obj[maxn], cnt[1<<maxm][1<<maxm];
int kase, n, m;

int dp(int s, int a) {
	if (cnt[s][a] <= 1) return 0;
	if (cnt[s][a] == 2) return 1;

	int &ans = d[s][a];
	if (vis[s][a] == kase) return ans;
	vis[s][a] = kase;

	ans = m;
	FOR(k, 0, m)
		if (!(s&(1 << k))) {
			int s2 = s | (1 << k), a2 = a | (1 << k);
			if (cnt[s2][a2] >= 1 && cnt[s2][a] >= 1) {
				int need = std::max(dp(s2, a), dp(s2, a2)) + 1;
				ans = std::min(ans, need);
			}
		}
	return ans;
}

void init() {
	int len = 1 << m;
	FOR(s, 0,len) {
		for (int i = s; i; i = (i - 1)&s) cnt[s][i] = 0;
		cnt[s][0] = 0;
	}
	FOR(i, 0, n) {
		int &tmp = obj[i];
		FOR(s, 0,len) ++cnt[s][s&tmp];
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &m, &n) == 2 && n&&m) {
		++kase; memset(obj, 0, sizeof(obj));
		FOR(i, 0, n) {
			scanf(" %s", str);
			int &tmp = obj[i];
			FOR(j, 0, m) if (str[j] == '1') tmp |= (1 << j);
		}
		init();
		printf("%d\n", dp(0, 0));
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}