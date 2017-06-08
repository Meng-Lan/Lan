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
	for (int i = static_cast<int>(n - r + 1); i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 100000 + 5;
int p[maxn], q[maxn];

int main() {
	int T;
	scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		int n;
		scanf("%d", &n);
		int totp = 0, totq = 0;
		FOR(i, n) {
			scanf("%d", p + i); totp += p[i];
		}
		FOR(i, n) {
			scanf("%d", q + i); totq += q[i];
		}
		if (totp < totq) printf("Case %d: Not possible\n", kase);
		else {
			int L = 0, R = 0, gas = 0;
			while (L < n) {
				gas = p[R];
				int ed = (L + n - 1) % n;
				while (R != ed) {
					if (gas - q[R] >= 0) {
						gas -= q[R];
						R = (R + 1) % n;
						gas += p[R];
					}
					else {
						L = R = (R + 1) % n; break;
					}
				}
				if (R == ed) {
					printf("Case %d: Possible from station %d\n", kase, L + 1);
					break;
				}
			}
		}
	}
	return 0;
}