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

const int maxn = 155;
int in[maxn][maxn], sum[maxn][maxn], n;

inline int Sum(int x1, int y1, int x2, int y2) {
	--x1; --y1;
	return sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1];
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		For(i, 1, n) For(j, 1, n) {
			scanf("%d", in[i] + j);
			in[i + n][j] = in[i][j + n] = in[i + n][j + n] = in[i][j];
		}
		int m = n << 1;
		For(i, 0, m) sum[i][0] = sum[0][i] = 0;
		int ans = 0;
		For(i, 1, m) For(j, 1, m)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + in[i][j];
		FOR(i, 0, m) {
			int len = std::min(m, i + n);
			For(j, i + 1, len) {
				std::priority_queue<P> q;
				For(k, 0, m) {
					while (!q.empty() && q.top().second < k - n) q.pop();
					if (!q.empty()) ans = std::max(ans, sum[j][k] - sum[i][k] + q.top().first);
					q.push(P(sum[i][k] - sum[j][k], k));
				}
			}
		}
		//For(i, 1, m) For(j, 1, m) printf("%d%c", sum[i][j], j == m ? '\n' : ' ');
		printf("%d\n", ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}