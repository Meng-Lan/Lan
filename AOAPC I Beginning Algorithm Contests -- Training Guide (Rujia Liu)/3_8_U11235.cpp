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

const int maxn = 1e5 + 10;
int in[maxn], num[maxn], l[maxn], r[maxn], cnt[maxn], d[maxn][20];

void RMQ_init(int n) {
	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 0; i + (1 << j) - 1 < n; ++i)
			d[i][j] = std::max(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
}

int RMQ(int L, int R) {
	if (in[L] == in[R]) return R - L + 1;
	int ans = std::max(r[L] - L + 1, R - l[R] + 1);
	L = num[L] + 1; R = num[R] - 1;
	if (L > R) return ans;
	int k = 0;
	while ((1 << (k + 1)) <= R - L + 1) ++k;
	return std::max(ans, std::max(d[L][k], d[R - (1 << k) + 1][k]));
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int n, q;
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d", &q);
		For(i, 1, n) scanf("%d", in + i);
		int t = 1, len = 0;
		For(i, 1, n) {
			if (in[i] != in[t]) {
				FOR(j, t, i) {
					num[j] = len;
					l[j] = t;
					r[j] = i - 1;
				}
				d[len++][0] = i - t;
				t = i;
			}
		}
		For(j, t, n) {
			num[j] = len;
			l[j] = t;
			r[j] = n;
		}
		d[len++][0] = n - t + 1;
		//For(i, 1, n) printf("#%d num:%d l:%d r:%d\n", i, num[i], l[i], r[i]);
		RMQ_init(len);
		int L, R;
		FOR(i, 0, q) {
			scanf("%d%d", &L, &R);
			printf("%d\n", RMQ(L, R));
		}
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}