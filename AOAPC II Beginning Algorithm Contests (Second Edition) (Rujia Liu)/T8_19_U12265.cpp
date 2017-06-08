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

const int maxn = 1005;
int height[maxn];
char s[maxn][maxn];
int ans[4 * maxn];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		FOR(i, n) scanf(" %s", s[i]);
		memset(height, 0, sizeof(height));
		memset(ans, 0, sizeof(ans));
		FOR(i, n) {
			stack<P> t;
			FOR(j, m) {
				if (s[i][j] == '.') {
					++height[j];
					P now(j, height[j]);
					if (t.empty()) t.push(now);
					else {
						while (!t.empty()) {
							P tmp = t.top(); t.pop();
							if (tmp.second > height[j]) tmp.second = height[j];
							if (now.second - now.first > tmp.second - tmp.first) {
								t.push(tmp);
								break;
							}
							else now = tmp;
						}
						t.push(now);
					}
					//printf("[%d,%d] (%d,%d)=%d\n", now.first, now.second, i, j, 2 * (j - now.first + 1 + now.second));
					++ans[2 * (j - now.first + 1 + now.second)];
				}
				else {
					height[j] = 0;
					while (!t.empty()) t.pop();
				}
			}
		}
		for (int i = 0; i < 4 * maxn; ++i)
			if (ans[i]) printf("%d x %d\n", ans[i], i);
	}
	return 0;
}