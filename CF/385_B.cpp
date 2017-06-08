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

const int maxn = 505;
char s[maxn][maxn];
int n, m;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &m);
	FOR(i, 0, n) scanf(" %s", s[i]);
	int sum = 0;
	FOR(i, 0, n) FOR(j, 0, m) if (s[i][j] == 'X') ++sum;
	bool ans = true;

	int bx = -1, by = -1, ex = -1, ey = -1;
	bool ok = false;
	FOR(i, 0, n) if (!ok) FOR(j, 0, m) if (s[i][j] == 'X') {
		bx = i, by = j; ok = true; break;
	}
	ok = false;
	for (int i = n - 1; i >= 0; --i) if (!ok) for (int j = m - 1; j >= 0; --j) if (s[i][j] == 'X') {
		ex = i, ey = j; ok = true; break;
	}
	int ts = 0;
	For(i, bx, ex) For(j, by, ey) {
		if (s[i][j] != 'X') ans = false;
		else ++ts;
	}
	if (ts != sum) ans = false;
	if (ans) printf("YES\n");
	else printf("NO\n");


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}