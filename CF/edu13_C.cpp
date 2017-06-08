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
ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

int main() {
	ll n, a, b, p, q;
	cin >> n >> a >> b >> p >> q;
	ll al = n / a, bl = n / b, t = n / lcm(a, b);
	ll ans = (al - t)*p + (bl - t)*q;
	if (p >= q) ans += p*t;
	else ans += q*t;
	cout << ans << endl;
	return 0;
}