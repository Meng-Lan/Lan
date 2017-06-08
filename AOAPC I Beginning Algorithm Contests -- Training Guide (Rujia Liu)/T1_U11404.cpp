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

const int INF = 1e9;
const int maxn = 1e3 + 10;
int d[maxn][maxn], vis[maxn][maxn], n, kase;
char s[maxn];
std::string t[maxn][maxn];

int dp(int l, int r,std::string &ts) {
	if (vis[l][r] == kase) return d[l][r];
	//printf("L:%d R:%d\n", l, r);
	int &ans = d[l][r]; vis[l][r] = kase; ts = "";
	if (l == r) {
		ts = s[l];
		return ans = 1;
	}
	if (l - r == 1) return ans = 0;
	if (l - r > 1) return ans = -INF;
	if (s[l] == s[r]) {
		ans = dp(l + 1, r - 1,t[l+1][r-1]) + 2;
		ts = s[l] + t[l+1][r-1] + s[r];
	}
	else {
		std::string &t1 = t[l + 1][r], &t2 = t[l][r - 1];
		ans = std::max(dp(l + 1, r, t1), dp(l, r - 1, t2));
		if (d[l + 1][r] == d[l][r - 1]) ts = std::min(t1, t2);
		else if (d[l + 1][r] > d[l][r - 1]) ts = t1;
		else ts = t2;
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%s", s) == 1) {
		n = strlen(s); ++kase;
		dp(0, n - 1, t[0][n - 1]);
		cout << t[0][n-1] << '\n';
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}