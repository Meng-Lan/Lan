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

const int maxn = 1e6 + 10;
char s[maxn];
int n, l, sum[maxn], q[maxn];

int cmp(int b, int e, int b2, int e2) {
	int left = (sum[e] - sum[b - 1])*(e2 - b2 + 1), right = (sum[e2] - sum[b2 - 1])*(e - b + 1);
	if (left > right) return 1;
	else if (left == right) return 0;
	else return -1;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d %s", &n, &l, s + 1);
		sum[0] = 0;
		For(i, 1, n) sum[i] = sum[i - 1] + (s[i] == '1');
		P ans(1, l);
		int i = 0, j = 0;
		For(t, l, n) {
			while (j - i > 1 && cmp(q[j - 2], t - l, q[j - 1], t - l) >= 0) --j;
			q[j++] = t - l + 1;
			while (j - i > 1 && cmp(q[i], t, q[i + 1], t) <= 0) ++i;
			int c = cmp(q[i], t, ans.first, ans.second);
			if (c > 0 || c == 0 && t - q[i] < ans.second - ans.first) {
				ans.first = q[i]; ans.second = t;
			}
		}
		printf("%d %d\n", ans.first, ans.second);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}