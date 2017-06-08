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
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef std::pair<ll, ll> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 100010;
int n, m;
P in[maxn];
std::pair<P, P> data[maxn][2];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	ll ans = 0;
	scanf("%d%d", &n, &m);
	For(i, 1, n) scanf("%lld", &in[i].first);
	For(i, 1, n) {
		scanf("%lld", &in[i].second);
		ll &c_z = in[i].second;
		std::pair<P, P> &t = data[c_z][i & 1];
		if (data[c_z][i & 1].first.first) {
			ans += t.first.second + t.second.first*in[i].first + t.second.second*i + t.first.first*i*in[i].first;
			ans %= 10007;
		}
		++t.first.first;
		t.first.second += in[i].first*i;
		t.second.first += i;
		t.second.second += in[i].first;
		//cout << ans << endl;
	}
	printf("%lld\n", ans);

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}