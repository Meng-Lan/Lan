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

const int maxn = 1005;
int d[maxn][6 * maxn], cnt[maxn], n;
ull a, b;

ull mul_mod(ull a, ull b, const int MOD) {
	if (b == 0) return 1;
	ull tmp = mul_mod(a, b >> 1, MOD);
	tmp = (tmp*tmp) % MOD;
	if (b & 1) tmp = (tmp*a) % MOD;
	return tmp;
}

int solve(ull a, ull b, int n) {
	if (a == 0 || n == 1) return 0;
	int p = mul_mod(a%cnt[n], b, cnt[n]);
	return d[n][p];
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	d[1][1] = 1;
	For(i, 2, 1000) {
		d[i][0] = 0; d[i][1] = 1;
		for (int j = 2;; ++j) {
			d[i][j] = (d[i][j - 1] + d[i][j - 2]) % i;
			if (d[i][j - 1] == 0 && d[i][j] == 1) {
				cnt[i] = j - 1;
				break;
			}
		}
	}
	int T; scanf("%d", &T);
	while (T--) {
		cin >> a >> b >> n;
		cout << solve(a, b, n) << '\n';
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}