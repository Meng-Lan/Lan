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
	int m = sqrt(len + 0.5);
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

const int maxn = 10;
char s[maxn][maxn], t[maxn][maxn];
int d[maxn], k;

std::string deal(int j) {
	char s1[maxn], s2[maxn];
	memset(s1, 0, sizeof(s1)); memset(s2, 0, sizeof(s2));
	FOR(i, 0, 6) { s1[i] = s[i][j]; s2[i] = t[i][j]; }
	std::sort(s1, s1 + 6); std::sort(s2, s2 + 6);
	int len1 = std::unique(s1, s1 + 6) - s1, len2 = std::unique(s2, s2 + 6) - s2;
	std::string tmp;
	FOR(i, 0, len1) {
		bool ok = true;
		FOR(j, 0, len2) if (s1[i] == s2[j]) {
			ok = false; break;
		}
		if (!ok) tmp += s1[i];
	}
	return tmp;
}

std::vector<std::string> init() {
	std::vector<std::string> ans;
	FOR(i, 0, 5) ans.push_back(deal(i));
	//FOR(i, 0, ans.size()) cout << ans[i] << '\n';
	d[5] = 1;
	for (int i = 4; i >= 0; --i) d[i] = d[i + 1] * ans[i].size();
	return ans;
}

void solve() {
	std::vector<std::string> tmp = init();
	if (k > d[0]) { puts("NO"); return; }
	--k;
	std::string ans;
	FOR(i, 0, 5) {
		ans += tmp[i][k / d[i + 1]];
		k %= d[i + 1];
	}
	cout << ans << '\n';
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &k);
		FOR(i, 0, 6) scanf(" %s", s[i]);
		FOR(i, 0, 6) scanf(" %s", t[i]);
		solve();
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}