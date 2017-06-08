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

const int maxn = 110;
ull d[maxn][maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	memset(d, 0, sizeof(d));
	for (int i = 1; i < maxn; ++i)
		for (int j = 1; j <= 63; ++j)
			d[i][j] = d[i - 1][j - 1] + 1 + d[i][j - 1];
	ull k, n;
	while (cin >> k >> n&&k) {
		int ans = -1;
		for (int i = 1; i <= 63; ++i)
			if (d[k][i] >= n) { ans = i; break; }
		if (ans < 0) printf("More than 63 trials needed.\n");
		else cout << ans << '\n';
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}