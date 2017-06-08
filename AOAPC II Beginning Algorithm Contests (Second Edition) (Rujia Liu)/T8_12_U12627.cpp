#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<functional>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair
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

ll c(int k) {
	ll ans = 1;
	FOR(i, k) ans *= 3;
	return ans;
}

ll g(int k, int i) {
	if (i <= 0) return 0;
	if (k == 0) return 1;
	if (i > (1 << k - 1)) return (ll)2 * g(k - 1, i - (1 << (k - 1))) + c(k-1);
	else return g(k - 1, i);
}

int main() {
	int T,kase=0;
	scanf("%d", &T);
	while (T--) {
		int k, a, b;
		scanf("%d%d%d", &k, &a, &b);
		int kkk = 1 << k;
		ll bgn = g(k, kkk - a + 1), ed = g(k, kkk - b);
		//cout << bgn << ' ' << ed << endl;
		printf("Case %d: %lld\n", ++kase, bgn - ed);
	}
	return 0;
}