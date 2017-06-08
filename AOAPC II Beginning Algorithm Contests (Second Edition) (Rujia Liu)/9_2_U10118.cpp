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
typedef unsigned long long ull;
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 45;
int d[maxn][maxn][maxn][maxn], in[4][maxn], n;

int dp(int *pos, int count, int color) {
	int &ans = d[pos[0]][pos[1]][pos[2]][pos[3]];
	if (ans >= 0) return ans;
	ans = 0;
	if (count == 5) return ans;
	FOR(i, 0, 4) {
		if (pos[i] == n) continue;
		++pos[i];
		if ((1 << (in[i][pos[i]]))&color) ans = std::max(ans, dp(pos, count - 1, color ^ (1 << (in[i][pos[i]]))) + 1);
		else ans = std::max(ans, dp(pos, count + 1, color | (1 << (in[i][pos[i]]))));
		--pos[i];
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		For(i,1, n) FOR(j, 0, 4) scanf("%d", in[j] + i);
		memset(d, -1, sizeof(d));
		int pos[4] = { 0,0,0,0 };
		printf("%d\n", dp(pos, 0, 0));
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}