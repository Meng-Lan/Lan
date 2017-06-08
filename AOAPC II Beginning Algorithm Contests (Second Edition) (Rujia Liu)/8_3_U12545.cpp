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

const int maxn = 105;
int T, len, one, one2, zero, zero2, question;
char s[maxn], t[maxn];

int main() {
	scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		one = one2 = zero = zero2 = question = 0;
		scanf(" %s %s", s, t);
		len = strlen(s);
		FOR(i, len) {
			if (s[i] == '0') ++zero;
			else if (s[i] == '1') ++one;
			else ++question;
			if (t[i] == '0') ++zero2;
			else ++one2;
		}

		if (one > one2) {
			printf("Case %d: -1\n", kase); continue;
		}
		int cone = one2 - one, ans = 0;
		FOR(i, len)
			if (s[i] == '?') {
				if (t[i] == '1'&&cone) {
					s[i] = '1';
					--cone;
				}
				else s[i] = '0';
				++ans;
			}
		FOR(i, len) if (s[i] != t[i] && s[i] == '0'&&cone) {
			s[i] = '1';
			++ans; --cone;
		}
		int change = 0;
		FOR(i, len) if (s[i] != t[i]) ++change;
		ans += change / 2;
		printf("Case %d: %d\n", kase, ans);
	}
	return 0;
}