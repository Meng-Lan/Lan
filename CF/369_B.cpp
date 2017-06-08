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
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }
std::vector<int> Eratosthenes(const int len, int *vis) {
	memset(vis, 0, sizeof(int)*len);
	std::vector<int> prime;
	int m = sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n, int *phi) {
	For(i, 2, n) phi[i] = 0;
	phi[1] = 1;
	For(i, 2, n) if (!phi[i])
		for (int j = i; j <= n; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i*(i - 1);
		}
}

const int maxn = 505;
ll in[maxn][maxn],n;

bool check(ll ans) {
	ll cnt = 0;
	FOR(i, 0, n) {
		cnt = 0;
		FOR(j, 0, n) cnt += in[i][j];
		if (cnt != ans) return false;
	}
	FOR(i, 0, n) {
		cnt = 0;
		FOR(j, 0, n) cnt += in[j][i];
		if (cnt != ans) return false;
	}
	cnt = 0;
	FOR(i, 0, n) cnt += in[i][n - i - 1];
	if (cnt != ans) return false;
	cnt = 0;
	FOR(i, 0, n) cnt += in[i][i];
	if (cnt != ans) return false;
	return true;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	P e;
	int cnt = 0;
	FOR(i, 0, n) FOR(j, 0, n) {
		scanf("%I64d", &in[i][j]);
		if (in[i][j] == 0) {
			e = P(i, j); ++cnt;
		}
	}
	assert(cnt <= 1);
	if (n == 1) {
		if (cnt)
			puts("1");
	}
	else {
		int x, y;
		FOR(i, 0, n) if (i != e.first) {
			x = i; break;
		}
		ll sum = 0;
		FOR(i, 0, n) sum += in[x][i];
		ll ans = sum;
		FOR(i, 0, n) ans -= in[e.first][i];
		in[e.first][e.second] = ans;
		if (check(sum) && ans >= 1) {
			printf("%I64d\n", ans);
		}
		else puts("-1");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}