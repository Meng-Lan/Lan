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

const int ma = 1234567, mb = 123456, mc = 1234;

int main() {
	int n;
	scanf("%d", &n);
	int off = false;
	for (int i = 0; i*ma <= n; ++i) {
		int m = n - i*ma;
		for (int j = 0; j*mb <= m; ++j) {
			int o = m - j*mb;
			if (o >= 0 && o%mc == 0)
				off = true;
		}
	}
	if (off)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}