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
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int mod = 1e9 + 7;

ll quick(ll x,ll n) {
	ll ans = 1, temp = x;
	while (n) {
		if (n & 1) ans = ans*temp%mod;
		n >>= 1;
		temp = temp*temp%mod;
	}
	return ans;
}

int main() {
	ll a, b, x, n;
	cin >> a >> b >> n >> x;
	ll temp = quick(a, n);
	ll ans;
	if (n == 1)
		ans = temp*x + b;
	else ans = temp*x + (1-temp)*b / (1-a);
	ans %= mod;
	cout << ans << endl;
	return 0;
}