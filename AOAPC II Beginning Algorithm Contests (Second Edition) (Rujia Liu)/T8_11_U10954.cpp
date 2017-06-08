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

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		priority_queue<int, vector<int>, greater<int>> q;
		int x;
		FOR(i, n) {
			scanf("%d", &x); q.push(x);
		}
		ll ans = 0;
		while (q.size()>1) {
			int a = q.top(); q.pop();
			int b = q.top(); q.pop();
			ans += a + b;
			q.push(a + b);
		}
		printf("%lld\n", ans);
	}
	return 0;
}