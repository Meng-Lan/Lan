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

const int maxn = (1 << 16) + 10;
ll d[maxn];
int vis[maxn], in[20], n, kase, S;
char str[20];

ll dp(int s) {
	if (s == S) return 1;
	if (vis[s] == kase) return d[s];
	vis[s] = kase; ll &ans = d[s];
	ans = 0;
	int s0 = s^S;
	int ki = 0;
	FOR(i, 0, n) if (s&(1 << i)) {
		FOR(j, 0, n) if ((in[i + 1] & (1 << j)) && (s0&(1 << j)))
			ki |= (1 << j);
	}
	FOR(j, 0, n) if ((in[0] & (1 << j)) && (s0&(1 << j))) ki |= (1 << j);
	FOR(i, 0, n) if (ki&(1 << i)) ans += dp(s | (1 << i));
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		++kase;
		scanf("%d", &n);
		For(i, 0, n) {
			scanf(" %s", str);
			in[i] = 0;
			FOR(j, 0, n) if (str[j] == '1') in[i] ^= (1 << j);
		}
		S = (1 << n) - 1;
		ll ans = 0;
		FOR(i, 0, n) if (in[0] & (1 << i)) ans += dp(1 << i);
		printf("Case %d: %lld\n", kase, ans);
		//FOR(i, 0, (1 << n)) printf("#%d %lld\n", i, d[i]);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}