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

const int INF = 1e9;
const int maxn = 105;
double d[maxn][maxn], sum[maxn], in[maxn];
int n, w, kase, vis[maxn][maxn];

double dp(int i, int j) {
	if (j <= 0) {
		if (i > n) return 0;
		else return INF;
	}
	if (vis[i][j] == kase) return d[i][j];
	vis[i][j] = kase;
	double &ans = d[i][j];
	ans = INF;
	For(k, i, n - j + 1) {
		//printf("i:%d j:%d dp[%d][%d]:%.4f k:%d * sum:%.4f :%.4f\n", i, j, k, j - 1, dp(k, j - 1), k - 1, sum[k - 1] - sum[i - 1], (k - 1)*(sum[k - 1] - sum[i - 1]));
		ans = std::min(ans, dp(k + 1, j - 1) + (k) * (sum[k] - sum[i - 1]));
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &w);
		in[0] = 0.0; ++kase;
		For(i, 1, n) { scanf("%lf", in + i);}
		std::sort(in + 1, in + n + 1);
		std::reverse(in + 1, in + n + 1);
		For(i, 1, n) in[i] += in[i - 1];
		//For(i, 0, n) printf("%.1f%c", in[i], i == n ? '\n' : ' ');
		sum[0] = 0.0;
		For(i, 1, n) sum[i] = sum[i - 1] + (in[i] - in[i - 1]) / in[n];
		//For(i, 0, n) printf("%.2f%c", sum[i], i == n ? '\n' : ' ');
		printf("%.4f\n", dp(1, w));
		//For(i, 1, n) For(j, 1, w) printf("%.2f%c", d[i][j], j == w ? '\n' : ' ');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}