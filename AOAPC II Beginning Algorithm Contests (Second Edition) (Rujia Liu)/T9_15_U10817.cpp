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

const int maxn = 125;;
const int maxs = 8;
const int INF = 1e9;
int m, n, s, c[maxn], st[maxn], d[maxn][1 << maxs][1 << maxs];

int dp(int i, int s0, int s1, int s2) {
	if (i == m + n) return s2 == (1 << s) - 1 ? 0 : INF;
	int &ans = d[i][s1][s2];
	if (ans >= 0) return ans;
	ans = INF;
	if (i >= m) ans = dp(i + 1, s0, s1, s2);
	int m0 = s0&st[i], m1 = s1&st[i];
	s0 ^= m0; s1 = (s1^m1) | m0; s2 |= m1;
	ans = std::min(ans, c[i] + dp(i + 1, s0, s1, s2));
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d%d", &s, &m, &n) == 3 && m&&n&&s) {
		std::string line;
		std::getline(cin, line);
		FOR(i, 0, m + n) {
			std::getline(cin, line);
			std::stringstream ss(line);
			ss >> c[i]; int t, tmp = 0;
			while (ss >> t) tmp |= (1 << (t - 1));
			st[i] = tmp;
		}
		memset(d, -1, sizeof(d));
		printf("%d\n", dp(0, (1 << s) - 1, 0, 0));
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}