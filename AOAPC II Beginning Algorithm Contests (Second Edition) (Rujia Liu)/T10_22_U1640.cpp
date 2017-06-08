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

const int maxn = 10;
const int cnt[maxn] = { 0,1,10,100,1000,10000,100000,1000000,10000000,100000000 };
ll f[maxn][maxn][maxn], d[2][maxn], g[maxn][maxn];;
int a, b;

int intlen(int t) {
	if (t == 0) return 1;
	int cnt = 0;
	while (t) { t /= 10; ++cnt; }
	return cnt;
}

int getint(char *s,int l,int r) {
	int ans = 1, base = 1;
	for (int i = r - 1; i >= l; --i) {
		if (s[i] - '0') ans += base*(s[i] - '0');
		base *= 10;
	}
	return ans;
}

void fd(int t, ll *cnt) {
	int len = intlen(t);
	char s[maxn];
	sprintf(s, "%d", t);
	//printf("S:%s len:%d\n", s, len);
	for (int i = len - 1; i >= 0; --i) {
		int num = getint(s, i + 1, len);
		cnt[s[i] - '0'] += num;
		//printf("i:%d s[i]:%c num:%d\n", i, s[i], num);
		FOR(j, 0, s[i] - '0') {
			if (j == 0) {
				//printf("i:%d j:%d\n", i, j);
				if (!i) FOR(k, 0, maxn) cnt[k] += f[len - i][j][k];
				else FOR(k, 0, maxn) cnt[k] += g[len - i][k];
			}
			else
				FOR(k, 0, maxn) cnt[k] += f[len - i][j][k];
			//FOR(k, 0, maxn) printf("%d ", cnt[k]); putchar('\n');
		}
	}
	FOR(i, 1, len) if (s[i] - '0') cnt[0] += ::cnt[len - i];
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	FOR(i, 0, maxn) { f[1][i][i] = 1; g[1][i] = 0; }
	FOR(i, 2, maxn) FOR(j, 0, maxn) {
		if (j == 0) {
			FOR(l, 0, maxn) FOR(k, 0, maxn) g[i][k] += f[i - 1][l][k];
			if (i > 2) g[i][0] += cnt[i - 1];
		}
		if (j == 0) {
			FOR(k, 0, maxn) f[i][j][k] = g[i][k];
		}
		else {
			FOR(k, 0, maxn) f[i][j][k] = g[i][k];
			f[i][j][j] += cnt[i];
		}
	}
	FOR(i, 2, maxn) {
		if (i != maxn - 1) {
			f[i + 1][0][0] = 0;
			FOR(j, 0, maxn) f[i + 1][0][0] += f[i][j][0];
		}
	}
	//FOR(i, 9, maxn) FOR(j, 0, maxn) printf("(%d,%d) = %lld & %lld\n", i, j, f[i][0][j], g[i][j]);
	while (scanf("%d%d", &a, &b) == 2 && a&&b) {
		if (a > b) std::swap(a, b);
		memset(d, 0, sizeof(d));
		fd(a - 1, d[0]);
		fd(b, d[1]);
		//FOR(i, 0, 2) { FOR(j, 0, maxn) printf("%d ", d[i][j]); putchar('\n'); }
		FOR(i, 0, maxn) printf("%lld%c", d[1][i] - d[0][i], (i == 9) ? '\n' : ' ');
	}


#ifdef MengLan
	//printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}