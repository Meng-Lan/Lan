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

const int maxn = 200010;
int n, k, m, in[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		FOR(i, 0, n) scanf("%d", in + i);
		int cnt = 0, l = 0, r = 0;
		//while (r < n&&cnt < k) if (in[r++] >= m) ++cnt;
		ll ans = 0;
		while (r < n) {
			while (cnt >= k) {
				if (in[l++] >= m) --cnt;
				if (cnt >= k) ans += n - r + 1;
			}
			if (in[r++] >= m) ++cnt;
			if (cnt >= k) ans += n - r + 1;
		}
		while (cnt >= k) {
			if (in[l++] >= m) --cnt;
			if (cnt >= k) ans += n - r + 1;
		}
		cout << ans << endl;
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}