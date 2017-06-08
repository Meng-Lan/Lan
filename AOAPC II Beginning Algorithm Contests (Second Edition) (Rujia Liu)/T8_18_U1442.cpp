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

const int maxn = 1000000 + 5;
int hight[maxn], under[maxn], h[maxn], n;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", under + i);
		for (int i = 1; i <= n; ++i) scanf("%d", hight + i);
		under[0] = under[n + 1] = hight[0] = hight[n + 1] = maxn;
		int level = hight[0];
		for (int i = 1; i <= n + 1; ++i) {
			if (level > hight[i]) level = hight[i];
			if (level < under[i]) level = under[i];
			h[i] = level;
		}
		level = hight[n + 1];
		for (int i = n; i >= 0; --i) {
			if (level > hight[i]) level = hight[i];
			if (level < under[i]) level = under[i];
			h[i] = min(level, h[i]);
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			ans += max(0, h[i] - under[i]);
		printf("%d\n", ans);
	}
	return 0;
}