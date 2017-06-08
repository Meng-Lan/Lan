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

const int maxn = 100000 + 10;
ll deal[maxn];
int in[maxn],pos[maxn], n, k;

bool cmp(const int &t1, const int &t2) { return in[t1] > in[t2]; }

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k); deal[0] = 0;
		FOR(i, 1, n) { scanf("%d", in + i); deal[i] = deal[i - 1] + in[i]; }
		if (k >= n) { printf("%d\n", n); continue; }
		FOR(i, 1, n) pos[i] = i;
		std::sort(pos + 1, pos + n, cmp);
		std::sort(pos + 1, pos + k);
		ll ans = 0; pos[0] = 0; pos[k] = n ;
		FOR(i, 0, k) {
			ll tmp = 0;
			if (pos[i] != pos[i + 1] - 1) tmp += deal[pos[i + 1]-1] - deal[pos[i]];
			tmp += pos[i + 1] - pos[i];
			ans += tmp;
		}
		cout << ans << '\n';
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}