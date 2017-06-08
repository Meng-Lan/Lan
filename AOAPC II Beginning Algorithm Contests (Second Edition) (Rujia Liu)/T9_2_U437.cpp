#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
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

const int maxn = 35;
int cube[maxn][3], d[maxn][3], n;

void get_dimensions(int *v, int b, int dim) {
	int idx = 0;
	FOR(i, 0, 3) if (i != dim) v[idx++] = cube[b][i];
}

int dp(int idx, int h) {
	int &ans = d[idx][h];
	if (ans >= 0) return ans;
	ans = 0;
	int v[2], v2[2];
	get_dimensions(v, idx, h);
	FOR(i, 0, n) FOR(j, 0, 3) {
		get_dimensions(v2, i, j);
		if (v2[0] < v[0] && v2[1] < v[1]) ans = std::max(ans, dp(i, j));
	}
	return ans += cube[idx][h];
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		FOR(i, 0, n) {
			FOR(j, 0, 3) scanf("%d", cube[i] + j);
			std::sort(cube[i], cube[i] + 3);
		}
		memset(d, -1, sizeof(d));
		int ans = 0;
		FOR(i, 0, n) FOR(j, 0, 3) ans = std::max(ans, dp(i, j));
		printf("Case %d: maximum height = %d\n", ++kase, ans);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}