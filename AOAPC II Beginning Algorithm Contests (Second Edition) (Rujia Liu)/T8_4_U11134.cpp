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

const int maxn = 5005;
P x[maxn], y[maxn], ans[maxn];
int xx[maxn], yy[maxn], n;

bool solve(P *t, int *ans) {
	memset(ans, -1, sizeof(int)*n);
	for (int i = 1; i <= n; ++i) {
		int Min = n + 1, idx = -1;
		for (int j = 0; j < n; ++j)
			if (ans[j] < 0 && t[j].second < Min&&i >= t[j].first) {
				idx = j; Min = t[j].second;
			}
		if (idx<0 || i>Min) return false;
		ans[idx] = i;
	}
	return true;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		FOR(i, n)
			scanf("%d%d%d%d", &x[i].first, &y[i].first, &x[i].second, &y[i].second);
		if (solve(x, xx) && solve(y, yy)) FOR(i, n) printf("%d %d\n", xx[i], yy[i]);
		else printf("IMPOSSIBLE\n");
	}
	return 0;
}