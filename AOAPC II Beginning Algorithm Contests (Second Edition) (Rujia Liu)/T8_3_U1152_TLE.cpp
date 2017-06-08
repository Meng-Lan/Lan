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

const int maxn = 4000 + 5;
int num[4][maxn];
map<int, int> t;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		FOR(i, n)
			FOR(j, 4)
			scanf("%d", num[j] + i);
		FOR(i, n)
			FOR(j, n)
			++t[num[0][i] + num[1][j]];
		ll ans = 0;
		FOR(i, n)
			FOR(j, n)
			ans += t[0 - num[2][i] - num[3][j]];
		cout << ans << endl;
	}
	return 0;
}