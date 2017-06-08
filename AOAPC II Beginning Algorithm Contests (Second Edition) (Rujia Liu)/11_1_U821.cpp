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

const int maxn = 105;
int id[maxn], d[maxn][maxn], cnt, u, v;

int ID(int x) {
	if (id[x] != 0) return id[x];
	return id[x] = ++cnt;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d%d", &u, &v) == 2 && u&&v) {
		memset(d, 0x3f, sizeof(d)); memset(id, 0, sizeof(id)); cnt = 0;
		do {
			int x = ID(u), y = ID(v);
			d[x][y] = 1;
		} while (scanf("%d%d", &u, &v) == 2 && u&&v);
		For(k, 1, cnt) For(i, 1, cnt) For(j, 1, cnt) d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
		int sum = 0;
		For(i, 1, cnt) For(j, 1, cnt) if (i != j) sum += d[i][j];
		//For(i, 1, cnt) For(j, 1, cnt) if (i != j) printf("d[%d][%d]: %d\n", i, j, d[i][j]);
		int num = (cnt)*(cnt - 1);
		//printf("sum:%d num:%d\n", sum, num);
		double ans = double(sum) / num;
		printf("Case %d: average length between pages = %.3f clicks\n", ++kase, ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}