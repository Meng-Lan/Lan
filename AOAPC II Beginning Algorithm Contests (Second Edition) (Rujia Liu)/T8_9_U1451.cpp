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

const int maxn = 1e6 + 10;
char s[maxn];
int sum[maxn], q[maxn];

ll cmp(int L1, int R1, int L2, int R2) {
	return (ll)(sum[R1] - sum[L1 - 1])*(R2 - L2 + 1) - (ll)(sum[R2] - sum[L2 - 1])*(R1 - L1 + 1);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, l;
		scanf("%d%d", &n, &l);
		scanf(" %s", s);
		sum[0] = 0;
		FOR(i, n) if (s[i] == '1') sum[i + 1] = sum[i] + 1;
		else sum[i + 1] = sum[i];
		int i = 0, j = 0, ansL = 1, ansR = l, L = l;
		for (int L = l; L <= n; ++L) {
			while (j - i > 1 && cmp(q[j - 1], L - l, q[j - 2], L - l) <= 0) --j;
			q[j++] = L - l + 1;
			while (j - i > 1 && cmp(q[i], L, q[i + 1], L) <= 0) ++i;
			ll c = cmp(q[i], L, ansL, ansR);
			if (c > 0 || c == 0 && L - q[i] < ansR - ansL) {
				ansL = q[i]; ansR = L;
			}
		}
		printf("%d %d\n", ansL, ansR);
	}
	return 0;
}