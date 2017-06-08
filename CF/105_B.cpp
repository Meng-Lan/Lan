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

int vp, vd, t, f, c;
const double eps = 1e-8;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	cin >> vp >> vd >> t >> f >> c;
	if (vp > vd || vp == vd&&t) { cout << "0\n"; return 0; }
	double x = (double)vp*t / (vd - vp) + t, time = x, princess = x*vp;
	int ans = 0;
	while (princess + eps < c) {
		++ans;
		x = princess / vd + f;
		time = x + (princess + x*vp) / (vd - vp);
		princess += time*vp;
		//printf("time:%f princess:%f\n", time, princess);
	}
	cout << ans << '\n';

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}