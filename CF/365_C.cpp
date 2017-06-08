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
typedef std::pair<double, double> P;
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

const int maxn = 10010;
P in[maxn];
int n, w, v, u;

bool cmp(double t) {
	bool state1 = true, state2 = true;
	FOR(i, 0, n) if (in[i].first - (in[i].second / u + t)*v > 0) { state1 = false; break; }
	FOR(i, 0, n) if (in[i].first - (in[i].second / u + t)*v < 0) { state2 = false; break; }
	return state1 || state2;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d%d", &n, &w, &v, &u);
	FOR(i, 0, n) scanf("%lf%lf", &in[i].first, &in[i].second);
	double l = 0.0, r = 1e10;
	if (cmp(0.0)) printf("%.10f\n", (double)w / u);
	else {
		for (int i = 0; i < 100; ++i) {
			double m = l + (r - l) / 2;
			if (cmp(m)) r = m;
			else l = m;
		}
		printf("%.10f\n", l + (double)w / u);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}