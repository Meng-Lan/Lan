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
typedef unsigned long long ull;
ull d, k, a, b, t;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	cin >> d >> k >> a >> b >> t;
	ull ans = ((ull)1 << 60);
	ans = std::min(ans, d*b);
	ans = std::min(ans, k*a + (d - k)*b);
	ull len = (d - k) / k, len2 = (d - k) % k;
	ans = std::min(ans, k*a + len*k*a + len*t + len2*b);
	if (len2) ++len;
	ans = std::min(ans, a*d + len*t);
	cout << ans << endl;



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}