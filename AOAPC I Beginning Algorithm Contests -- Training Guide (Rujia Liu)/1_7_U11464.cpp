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
	int m = (int)sqrt(len + 0.5);
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

const int maxn = 20;
const int INF = 1e9;
int n, A[maxn][maxn], B[maxn][maxn];

int check(int s) {
	memset(B, 0, sizeof(B));
	FOR(i, 0, n) {
		if ((s >> i) & 1) B[0][i] = 1;
		else if (A[0][i] == 1) return INF;
	}
	FOR(i, 1, n) FOR(j, 0, n) {
		int sum = 0;
		if (i > 1) sum += B[i - 2][j];
		if (j > 0) sum += B[i - 1][j - 1];
		if (j < n - 1) sum += B[i - 1][j + 1];
		B[i][j] = sum % 2;
		if (A[i][j] == 1 && B[i][j] == 0) return INF;
	}
	int cnt = 0;
	FOR(i, 0, n) FOR(j, 0, n) if (A[i][j] != B[i][j]) ++cnt;
	return cnt;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	For(kase, 1, T) {
		scanf("%d", &n);
		FOR(r, 0, n) FOR(c, 0, n) scanf("%d", A[r] + c);
		int ans = INF;
		FOR(s, 0, (1 << n))
			ans = std::min(ans, check(s));
		if (ans == INF) ans = -1;
		printf("Case %d: %d\n", kase, ans);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}